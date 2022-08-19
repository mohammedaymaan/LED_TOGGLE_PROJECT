#ifndef  DIO_INTERFACE_H
#define  DIO_INTERFACE_H

typedef enum
{
  DIO_PORTA,
  DIO_PORTB,
  DIO_PORTC,
  DIO_PORTD,
  DIO_PORTE,
  DIO_PORTF
} Dio_PortType;

typedef uint8 Dio_LevelType;
typedef uint8 Dio_PortLevelType;

typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;


typedef enum 
{
    DIO_CHANNEL_A0,
    DIO_CHANNEL_A1,
    DIO_CHANNEL_A2,
    DIO_CHANNEL_A3,
    DIO_CHANNEL_A4,
    DIO_CHANNEL_A5,
    DIO_CHANNEL_A6,
    DIO_CHANNEL_A7,

    DIO_CHANNEL_B0,
    DIO_CHANNEL_B1,
    DIO_CHANNEL_B2,
    DIO_CHANNEL_B3,
    DIO_CHANNEL_B4,
    DIO_CHANNEL_B5,
    DIO_CHANNEL_B6,
    DIO_CHANNEL_B7,

    DIO_CHANNEL_C0,
    DIO_CHANNEL_C1,
    DIO_CHANNEL_C2,
    DIO_CHANNEL_C3,
    DIO_CHANNEL_C4,
    DIO_CHANNEL_C5,
    DIO_CHANNEL_C6,
    DIO_CHANNEL_C7,

    DIO_CHANNEL_D0,
    DIO_CHANNEL_D1,
    DIO_CHANNEL_D2,
    DIO_CHANNEL_D3,
    DIO_CHANNEL_D4,
    DIO_CHANNEL_D5,
    DIO_CHANNEL_D6,
    DIO_CHANNEL_D7,

    DIO_CHANNEL_E0,
    DIO_CHANNEL_E1,
    DIO_CHANNEL_E2,
    DIO_CHANNEL_E3,
    DIO_CHANNEL_E4,
    DIO_CHANNEL_E5,
    DIO_CHANNEL_E6,
    DIO_CHANNEL_E7,

    DIO_CHANNEL_F0,
    DIO_CHANNEL_F1,
    DIO_CHANNEL_F2,
    DIO_CHANNEL_F3,
    DIO_CHANNEL_F4,

}Dio_ChannelType;

typedef enum
{
    DIO_PORT_A,
    DIO_PORT_B,
    DIO_PORT_C,
    DIO_PORT_D,
    DIO_PORT_E,
    DIO_PORT_F

}Dio_PortType;


typedef struct
{
  Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
  Dio_PortType ports[DIO_CONFIGURED_PORTS];
  Dio_ChannelGroupType groups[DIO_CONFIGURED_GROUPS];
} Dio_ConfigType;


 Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/* Function for DIO write Channel API */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Function for DIO read Port API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function for DIO write Port API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Function for DIO Initialization API */
void Dio_Init(Dio_ConfigType *ConfigPtr);

/* Function for DIO flip channel API */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern Dio_ConfigType Dio_Configuration;

#endif /* DIO_H */


#endif 
