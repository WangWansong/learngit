/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: Close */
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: Reset */
#define  PANEL_COMMANDBUTTON_2            3       /* control type: command, callback function: Delet */
#define  PANEL_COMMANDBUTTON_3            4       /* control type: command, callback function: Divide */
#define  PANEL_COMMANDBUTTON_4            5       /* control type: command, callback function: input7 */
#define  PANEL_COMMANDBUTTON_5            6       /* control type: command, callback function: input8 */
#define  PANEL_COMMANDBUTTON_6            7       /* control type: command, callback function: input9 */
#define  PANEL_COMMANDBUTTON_7            8       /* control type: command, callback function: Multiply */
#define  PANEL_COMMANDBUTTON_8            9       /* control type: command, callback function: input4 */
#define  PANEL_COMMANDBUTTON_9            10      /* control type: command, callback function: input5 */
#define  PANEL_COMMANDBUTTON_10           11      /* control type: command, callback function: input6 */
#define  PANEL_COMMANDBUTTON_11           12      /* control type: command, callback function: Minus */
#define  PANEL_COMMANDBUTTON_12           13      /* control type: command, callback function: input1 */
#define  PANEL_COMMANDBUTTON_13           14      /* control type: command, callback function: input2 */
#define  PANEL_COMMANDBUTTON_14           15      /* control type: command, callback function: input3 */
#define  PANEL_COMMANDBUTTON_15           16      /* control type: command, callback function: Plus */
#define  PANEL_COMMANDBUTTON_16           17      /* control type: command, callback function: Sign */
#define  PANEL_COMMANDBUTTON_17           18      /* control type: command, callback function: input0 */
#define  PANEL_COMMANDBUTTON_18           19      /* control type: command, callback function: Point1 */
#define  PANEL_COMMANDBUTTON_19           20      /* control type: command, callback function: Equal */
#define  PANEL_STRING                     21      /* control type: string, callback function: (none) */
#define  PANEL_TEXTMSG                    22      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Close(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Delet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Divide(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Equal(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK input9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Minus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Multiply(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Plus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Point1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Reset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Sign(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
