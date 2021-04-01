/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow usage of the floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

#define USBFS_DEVICE    (0u)

/* The buffer size is equal to the maximum packet size of the IN and OUT bulk
* endpoints.
*/
#define USBUART_BUFFER_SIZE (64u)
#define LINE_STR_LENGTH     (45u)
char8* parity[] = {"None", "Odd", "Even", "Mark", "Space"};
char8* stop[]   = {"1", "1.5", "2"};

int main(void)
{
    uint16 count;
    uint8 buffer[USBUART_BUFFER_SIZE];
    uint8 state;
    char8 lineStr[LINE_STR_LENGTH];
    float stateVector[6];
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
    
    int ledState = BoardLed_Read();    
   
    for(;;)
    {
        /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_IsConfigurationChanged()) //Si la configaración ha cambiado
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_GetConfiguration())
            {
                /* Enumeration is done, enable OUT endpoint to receive data 
                 * from host. */
                USBUART_CDC_Init();
            }
        }
        
        /* Service USB CDC when device is configured. */
        if (0u != USBUART_GetConfiguration()) /* Si el puerto ha sido configurado */
        {
            /* Check for input data from host. */
            if (0u != USBUART_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                count = USBUART_GetAll(buffer); /* Recibe todo el paquete y re-habilita puntos de salida */
                //sprintf(lineStr,"\nLlegaron %d caracteres",count-1);
                
                /* Wait until component is ready to send data to host. */
                //while (0u == USBUART_CDCIsReady()){}
                //USBUART_PutString(lineStr);
                if (0u != count)
                {
                    /* Wait until component is ready to send data to host. */
                    while (0u == USBUART_CDCIsReady()){}
                    /* Send data back to host. */
                    USBUART_PutData(buffer, count); /* Devuelve la información que haya entrado */
                    
                    
                    
                    /* Wait until component is ready to send data to host. */
                    //while (0u == USBUART_CDCIsReady()){}
                    //USBUART_PutString("\n Envio confirmado\n");
                    /* If the last sent packet is exactly the maximum packet 
                    *  size, it is followed by a zero-length packet to assure
                    *  that the end of the segment is properly identified by 
                    *  the terminal.
                    */
                    if (USBUART_BUFFER_SIZE == count)
                    {
                        /* Wait until component is ready to send data to PC. */
                        while (0u == USBUART_CDCIsReady()){}

                        /* Send zero-length packet to PC. */
                        USBUART_PutData(NULL, 0u);
                    }
                }
            }


        #if (CY_PSOC3 || CY_PSOC5LP)
            /* Check for Line settings change. */
            /* Control de cambios en la configuracion */
            state = USBUART_IsLineChanged();
            if (0u != state)
            {
                /* Output Line Coding settings. */
                /* Muestra la configuracion*/
                if (0u != (state & USBUART_LINE_CODING_CHANGED))
                {                  
                    /* Get string to output. */
                    /*Obtiene los valores de configuración del puerto en un String*/
                    sprintf(lineStr,"\nBR:%4ld %d%c%s", USBUART_GetDTERate(),\
                    (uint16) USBUART_GetDataBits(),\
                    parity[(uint16) USBUART_GetParityType()][0],\
                    stop[(uint16) USBUART_GetCharFormat()]);
                    
                    /* Wait until component is ready to send data to host. */
                    while (0u == USBUART_CDCIsReady()){}
                    USBUART_PutString(lineStr); /* Envía configuración del puerto */

                }

                /* Output Line Control settings. */
                if (0u != (state & USBUART_LINE_CONTROL_CHANGED))
                {                   
                    /* Get string to output. */
                    state = USBUART_GetLineControl();
                    sprintf(lineStr,"\nDTR:%s,RTS:%s",  (0u != (state & USBUART_LINE_CONTROL_DTR)) ? "ON" : "OFF",
                                                      (0u != (state & USBUART_LINE_CONTROL_RTS)) ? "ON" : "OFF");
                    
                    /* Wait until component is ready to send data to host. */
                    while (0u == USBUART_CDCIsReady()){}
                    USBUART_PutString(lineStr);
                }
            }
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        }
        
        /* Control rápido de comunicación */
        /* Se envía un string cada vez que se presiona el botón de la placa */
        if(BoardLed_Read() != ledState){
            ledState = BoardLed_Read();
            /* Wait until component is ready to send data to host. */
            while (0u == USBUART_CDCIsReady()){}
            if( ledState ) USBUART_PutString("\n\rLed encendido");
            else USBUART_PutString("\n\rLed apagado");
        }
    }
}

/* [] END OF FILE */
