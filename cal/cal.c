#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>

#include "cal.h"
/******
	文件描述： 实习简易计算器
    人员    ：  王琬淞
	 时间：		2020.9.15



*****/
static int panelHandle;
char numA[100],numB[100];					 //定义计算的两个数字（字符串）
float numa=0.0,numb=0.0,Result=0.0;			 //定义数字和计算结果
int numFlag=0,calFlag=0;					 //定义处理数字的位数和计算符号位标志（1为/，2为*，3为-，4为+）
int signFlag[2]={1,1};						 //定义正负符号位


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "cal.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

void Transform()							 //字符串数字和double数字转化
{
	numa=atof(numA); 
	numb=atof(numB); 
	if(signFlag[0]==-1)						//由于无法将正负号在数字和字符串之间传递，设置符号位，并及时修正数字正负
	{
	  numa=-numa;	
	}
	if(signFlag[1]==-1)						//修复2号数字正负
	{
	  numb=-numb;	
	} 
}
void Show()									 //显示
{														//正负输出辅助
	char mit[101];
	memset(mit,0,sizeof(mit)) ; 
	strcat(mit,"-");   
	Transform();
	if(numFlag==0)										//是否为第一个数据输入
	{													//是否第一个数据为正
		if(signFlag[0]==1)
		{
		   SetCtrlVal(panelHandle,PANEL_STRING,numA);
		}
		else  
		{
		   strcat(mit,numA);
		   SetCtrlVal(panelHandle,PANEL_STRING,mit); 
		}
	}
	else if(numFlag==1&&calFlag!=0)					   //第二个数据输入
	{												   //第二个数据正负
			if(signFlag[1]==1)
			{
               SetCtrlVal(panelHandle,PANEL_STRING,numB);
			}
	      	else if(signFlag[1]==-1) 
		    {
		       strcat(mit,numB); 
	       	   SetCtrlVal(panelHandle,PANEL_STRING,mit); 
		    }
	}
 }
void Re()									 //部分清空，用于完成一次计算后
{
     numb=0;
     calFlag=0;
     signFlag[1]=1;
     memset(numB,0,sizeof(numB)) ;
}
void GetResult()							 //计算结果
{
	Transform();
											//判断运算标志位并进行计算
	if(calFlag==1)
		Result=numa/numb;
	else if (calFlag==2) 
		Result=numa*numb;
	else if (calFlag==3) 
		Result=numa-numb; 
	else if (calFlag==4) 
		Result=numa+numb; 
	
	numa=Result;							  //修复标志位
	if(numa<0)
	{
		signFlag[0]=-1;
		numa=-numa;
	}
	else
		signFlag[0]=1;     
	
    sprintf(numA,"%f",numa);
	char mit[101];
    strcat(mit,"-");
	
		if(signFlag[0]==1)								 //输出运算结果为正
            SetCtrlVal(panelHandle,PANEL_STRING,numA);
		else  											 //结果为负
		{
		  	strcat(mit,numA); 
	        SetCtrlVal(panelHandle,PANEL_STRING,mit); 
		}
	Re();
}
	
int CVICALLBACK Reset (int panel, int control, int event,	  //重置
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
		numFlag=0;
		signFlag[0]=1;
		signFlag[1]=1;
		numa=0;
		numb=0;
		Result=0;
		memset(numA,0,sizeof(numA));
		memset(numB,0,sizeof(numB));  
		break;
	} 
	Show();  
	return 0;
}

int CVICALLBACK Delet (int panel, int control, int event,	  //退格
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0&&numA[0]!=0)				  //第一个数据，且不为空
			{
			numA[strlen(numA)-1]='\0';
			}
			else if (numFlag==1&&numB[0]!=0)		  // 第二个数据且不为空
			{
			numB[strlen(numB)-1]=0; 
			}	
			break;
	}
		Show();
	return 0;
}

int CVICALLBACK Divide (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)	   //除
{
	
	switch (event)
	{
		case EVENT_COMMIT: 
	
	if(numB[0]!=0)						   //第二个数据不为空，进行运算
		GetResult();
	else								   //空，改变运算标志位
		numFlag=1;
	
    calFlag=1;	  
			break;
	}
	
	return 0;
}

int CVICALLBACK input7 (int panel, int control, int event,														  //输入数字7
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)						  //控制第一个数据时
			{ 
				strcat(numA,"7");
			}
			else if(numFlag==1)					 //控制第二个数据时
			{ 
				strcat(numB,"7");
			}
		Show(); 
		break;
	}	 	  
	return 0;
}

int CVICALLBACK input8 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)							//控制第一个数据时 
			{
				strcat(numA,"8");
			}
			else if(numFlag==1)						  //控制第2个数据时 
			{
		      	strcat(numB,"8");
			}
	    	Show();
		break;
	} 	 
	return 0;
}

int CVICALLBACK Multiply (int panel, int control, int event,												   //乘
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			
		case EVENT_COMMIT:
	        if(numB[0]!=0)						//第二个数据不为空，进行运算  
	    	   GetResult();
		    else
		       numFlag=1;						 //空，改变运算标志位
		
	      	calFlag=2;
		break;
	}

	return 0;
}

int CVICALLBACK input4 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"4");
			}
			else if(numFlag==1)
			{
				strcat(numB,"4");
			}
	     	Show(); 
		break;
	}	  
	return 0;
}

int CVICALLBACK input5 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"5");
			}
			else if(numFlag==1)
			{
				strcat(numB,"5");
			}
			Show();
			break;
	}   	   
	return 0;
}

int CVICALLBACK input6 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"6");
			}
			else if(numFlag==1)
			{
				strcat(numB,"6");
			}
		    Show();
		break;
	}  	   
	return 0;
}
																											  //减
int CVICALLBACK Minus (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
		  		
            	if(numB[0]!=0)
		           GetResult();
		        else
		           numFlag=1;
		
		        calFlag=3;
			break;
	}
	
	return 0;
}

int CVICALLBACK input1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"1");
			}
			else if(numFlag==1)
			{
			strcat(numB,"1");
			}
			Show();
			break;
	}     
	return 0;
}

int CVICALLBACK input2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
		         if(numFlag==0)
		    	{
				strcat(numA,"2");
		    	}
				else if(numFlag==1)
				{
				strcat(numB,"2");
				}
			    Show();
			break;
	} 	   
	return 0;
}

int CVICALLBACK input3 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
		    {
				strcat(numA,"3");
			}
			else if(numFlag==1)
			{
				strcat(numB,"3");
			}
		    Show();
		break;
	} 	  
	return 0;
}

int CVICALLBACK Plus (int panel, int control, int event,													 //加
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
        	if(numB[0]!=0)
		      GetResult();
		    else
		      numFlag=1;
			
		    calFlag=4;
		break;
	}
	return 0;
}
   
int CVICALLBACK input9 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"9");
			}
			else if(numFlag==1)
			{
				strcat(numB,"9");
			}
			Show();
			break;
	}    
	return 0;
}
int CVICALLBACK Sign (int panel, int control, int event,												//正负号翻转	
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)						   //是否操作第一个数据
			{
			 	signFlag[0]=-signFlag[0];
			}
				else if(numFlag==1&&numB[0]!='\0')	  //操作第二个数据，且不为空
			{
	        	signFlag[1]=-signFlag[1];  
			}
		    Show();
		break;
	}
	
	return 0;
}

int CVICALLBACK input0 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
			    if(numFlag==0)
			    {
			       strcat(numA,"0");
		     	}
	        	else if(numFlag==1)
			    {
			        strcat(numB,"0");
			    }
		        Show();
		break;
	} 	   
	return 0;
}

int CVICALLBACK Point1 (int panel, int control, int event,												    //小数点输入  
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
			    if(numFlag==0)					   //是否操作第一个数据
			    {
				    int pointFlag=0;			   //检测是否已有小数点存在
				    for(int i=0;i<100;i++)		  //扫描全部字符找小数点
				   {
					if(numA[i]==".")
						pointFlag=1;
					
				    }
				    if(pointFlag==0)			 //无小数点则输入小数点，有则无操作
				    {
					strcat(numA,".");
				    }
		         }
				else if(numFlag==1)				 //是否操作第二个数据，同上
				{
				    int pointFlag=0;
			     	for(int i=0;i<100;i++)
				    {
					    if(numB[i]==".")
						   pointFlag=1;
				    }
			    	if(pointFlag==0)
				    {
					   strcat(numB,".");
				    }
				}
		       Show();
		break;
	}
	
	return 0;
}

int CVICALLBACK Equal (int panel, int control, int event,												   //计算结果
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			 		
        	if(numB[0]!=0)						//如果第二个数据不为空，执行运算
		      GetResult();
		break;
	}
	return 0;
}

int CVICALLBACK Close (int panel, int event, void *callbackData,	 //退出
					   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);						   //点击退出
			break;
	}
	return 0;
}
