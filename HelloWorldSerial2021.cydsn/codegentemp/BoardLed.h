/*******************************************************************************
* File Name: BoardLed.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BoardLed_H) /* Pins BoardLed_H */
#define CY_PINS_BoardLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BoardLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BoardLed__PORT == 15 && ((BoardLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BoardLed_Write(uint8 value);
void    BoardLed_SetDriveMode(uint8 mode);
uint8   BoardLed_ReadDataReg(void);
uint8   BoardLed_Read(void);
void    BoardLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   BoardLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BoardLed_SetDriveMode() function.
     *  @{
     */
        #define BoardLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BoardLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BoardLed_DM_RES_UP          PIN_DM_RES_UP
        #define BoardLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define BoardLed_DM_OD_LO           PIN_DM_OD_LO
        #define BoardLed_DM_OD_HI           PIN_DM_OD_HI
        #define BoardLed_DM_STRONG          PIN_DM_STRONG
        #define BoardLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BoardLed_MASK               BoardLed__MASK
#define BoardLed_SHIFT              BoardLed__SHIFT
#define BoardLed_WIDTH              1u

/* Interrupt constants */
#if defined(BoardLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BoardLed_SetInterruptMode() function.
     *  @{
     */
        #define BoardLed_INTR_NONE      (uint16)(0x0000u)
        #define BoardLed_INTR_RISING    (uint16)(0x0001u)
        #define BoardLed_INTR_FALLING   (uint16)(0x0002u)
        #define BoardLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BoardLed_INTR_MASK      (0x01u) 
#endif /* (BoardLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BoardLed_PS                     (* (reg8 *) BoardLed__PS)
/* Data Register */
#define BoardLed_DR                     (* (reg8 *) BoardLed__DR)
/* Port Number */
#define BoardLed_PRT_NUM                (* (reg8 *) BoardLed__PRT) 
/* Connect to Analog Globals */                                                  
#define BoardLed_AG                     (* (reg8 *) BoardLed__AG)                       
/* Analog MUX bux enable */
#define BoardLed_AMUX                   (* (reg8 *) BoardLed__AMUX) 
/* Bidirectional Enable */                                                        
#define BoardLed_BIE                    (* (reg8 *) BoardLed__BIE)
/* Bit-mask for Aliased Register Access */
#define BoardLed_BIT_MASK               (* (reg8 *) BoardLed__BIT_MASK)
/* Bypass Enable */
#define BoardLed_BYP                    (* (reg8 *) BoardLed__BYP)
/* Port wide control signals */                                                   
#define BoardLed_CTL                    (* (reg8 *) BoardLed__CTL)
/* Drive Modes */
#define BoardLed_DM0                    (* (reg8 *) BoardLed__DM0) 
#define BoardLed_DM1                    (* (reg8 *) BoardLed__DM1)
#define BoardLed_DM2                    (* (reg8 *) BoardLed__DM2) 
/* Input Buffer Disable Override */
#define BoardLed_INP_DIS                (* (reg8 *) BoardLed__INP_DIS)
/* LCD Common or Segment Drive */
#define BoardLed_LCD_COM_SEG            (* (reg8 *) BoardLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define BoardLed_LCD_EN                 (* (reg8 *) BoardLed__LCD_EN)
/* Slew Rate Control */
#define BoardLed_SLW                    (* (reg8 *) BoardLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BoardLed_PRTDSI__CAPS_SEL       (* (reg8 *) BoardLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BoardLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BoardLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BoardLed_PRTDSI__OE_SEL0        (* (reg8 *) BoardLed__PRTDSI__OE_SEL0) 
#define BoardLed_PRTDSI__OE_SEL1        (* (reg8 *) BoardLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BoardLed_PRTDSI__OUT_SEL0       (* (reg8 *) BoardLed__PRTDSI__OUT_SEL0) 
#define BoardLed_PRTDSI__OUT_SEL1       (* (reg8 *) BoardLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BoardLed_PRTDSI__SYNC_OUT       (* (reg8 *) BoardLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BoardLed__SIO_CFG)
    #define BoardLed_SIO_HYST_EN        (* (reg8 *) BoardLed__SIO_HYST_EN)
    #define BoardLed_SIO_REG_HIFREQ     (* (reg8 *) BoardLed__SIO_REG_HIFREQ)
    #define BoardLed_SIO_CFG            (* (reg8 *) BoardLed__SIO_CFG)
    #define BoardLed_SIO_DIFF           (* (reg8 *) BoardLed__SIO_DIFF)
#endif /* (BoardLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(BoardLed__INTSTAT)
    #define BoardLed_INTSTAT            (* (reg8 *) BoardLed__INTSTAT)
    #define BoardLed_SNAP               (* (reg8 *) BoardLed__SNAP)
    
	#define BoardLed_0_INTTYPE_REG 		(* (reg8 *) BoardLed__0__INTTYPE)
#endif /* (BoardLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BoardLed_H */


/* [] END OF FILE */
