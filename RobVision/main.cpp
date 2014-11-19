#include <iostream>
#include <time.h>  
#include "../RobVisionSys/robVision.h"

using namespace std;

////! [main program]
//#include <QtWidgets>
//
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    QWidget window;
////! [create, lay out widgets and show]
//    QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
//    QLineEdit *lineEdit = new QLineEdit();
//
//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->addWidget(label);
//    layout->addWidget(lineEdit);
//    window.setLayout(layout);
////! [create, lay out widgets and show]
//    window.setWindowTitle(
//       QApplication::translate("windowlayout", "Window layout"));
//    window.show();
//    return app.exec();
//}
////! [main program]


int main(int argc, char* argv[])
{
    sbsRobSys robSys;
	robSys.connectLaserAsynchronousMode();
    robSys.loadPositionFromFile("recorded_position.csv");

    time_t rawtime;
    int num, degree;
	unsigned int pos;
    double v[6];
    double x,y,z;
	double wt;
    char userinput[256], filename[256], filename2[256], cmd[256];
    char command;
    char *index, *option;
	position temp[5];

	do
	{
	    command = NULL;
		printf("\n\ta:add current profile\n");
		printf("\tc:clear all profile\n");
		printf("\ts:save profile \t\t\ts |s [filename] |s [filename] [option]\n");
		printf("\t0:get rob position\n");
		printf("\t1:get joint values\n");
		printf("\t2:move tcp by\t\t\t2 [X] [Y] [Z]\n");
		printf("\t3:move joint to\t\t\t3 [v1] [v2] [v3] [v4] [v5] [v6]\n");
		printf("\t8:scan line segmentation\t8 [readfile]\n");
		printf("\t9:viewpoint planning based on scan line segmentation\t9 [readfile]\n");
		printf("\tg:angular scan\t\t\tg [degree] [numofscan]\n");
		printf("\td:dynamic angular scan\t\td [degree] [numofscan]\n");
		printf("\th:pipe scan \t\t\th [no of scan]\n");
		printf("\tu:calibration translation scan \tu [filename]\n");
		printf("\tt:perform multiple scan\t\tt [read_from] [save_to]\n");
		printf("\te:set exposure\t\t\te [exposure value]\n");
		printf("\tf:set frame rate\t\tf [frame_rate value]\n");
		printf("\tm:move to position\n");
		printf("\tl:multiple linear scan\t\tl [readfile] [numofscan]\n");
		printf("\tb:Temp scan\n");
		printf("\tv:viewpoint path scan\tv [readfile]\n");
		printf("\tx:linear scan\t\t\tx [v1] [v2] [v3] [v4] [v5] [v6] [x] [y] [z] [numofscan] [wt]\n");
		printf("\ty:dynamic linear scan\t\ty [v1] [v2] [v3] [v4] [v5] [v6] [x] [y] [z] [numofscan]\n");
		printf("\tz:exit program.\n");
		printf("\tEnter:");

		gets(userinput);
		if(strlen(userinput)>0)
        {
            index = strtok(userinput," ");
            command = *index;
        }

		switch(command)
		{
		    case 'a': printf("Add current profile\n");
					  robSys.addOnePolygon();
                      break;
            case 'c': printf("Clear all profile\n");
					  robSys.clearPolygons();
                      break;
            case 's': printf("Saving profile\n");
                      index = strtok(NULL," ");
                      if(index!=NULL)
                        strcpy(filename, index);
                      else
                      {
                          time(&rawtime);
                          strftime(filename,80,"robvision_%Y%m%d_%H%M%S", localtime(&rawtime));
                      }

                      strcat(filename, ".csv");
                      printf("File name = %s\n", filename);
                      option = strtok(NULL," ");

                      if(option!=NULL)
                        printf("Option = %s\n", option);
					  robSys.savePolygons(filename,option);
                      break;
            case '0': printf("Rob Position = \n");
					  //Do get tcp value
                      break;
            case '1': printf("Joint Value = \n");
					  //Do get joint value
                      break;
            case '2': printf("Move TCP by\n");
                      index = strtok(NULL," ");

                      if(index!=NULL)
						  x = atof(index);
					  else
						  break;
                      index = strtok(NULL," ");

					  if(index!=NULL)
                          y = atof(index);
					  else
						  break;

                      index = strtok(NULL," ");
                      if(index!=NULL)
                          z = atof(index);

                      printf("X = %f, Y = %f, Z = %f\n", x, y, z);
					  robSys.m_robot.move(x,y,z);
                      break;
            case '3': printf("Move joint to\n");
                      for(int i = 0; i<6; i++)
                      {
                            index = strtok(NULL," ");
                            if(index!=NULL)
                            {
                                v[i] = atof(index);
                            }
                      }
					  printf("V1 = %f, V2 = %f, V3 = %f,\n V4 = %f, V5 = %f, V6 = %f\n", v[0], v[1], v[2], v[3], v[4], v[5]);
					  robSys.moveJointTo(v[0], v[1], v[2], v[3], v[4], v[5]);
					  break;

			 case '8':
					  printf("\t Labelling the scan lines\n");
					  index = strtok(NULL," ");
                      if(index!=NULL)
						  strcpy(filename, index);
					  else
						  break;
					  sprintf(cmd,"RV_labelling.exe %s",filename);
					  system(cmd);
					  break;
			case '9':
					  printf("\t Viewpoint Planning\n");
					  index = strtok(NULL," ");
                      if(index!=NULL)
						  strcpy(filename, index);
					  else
						  break;
					  sprintf(cmd,"RV_viewplanning.exe %s",filename);
					  system(cmd);
					  break;
			 case 'm':	if(robSys.recorded_position.size() == 0)
						{
							cout << "no recorded position loaded\n";
							break;
						}
						cout << "\nList of recorded position\n";
						robSys.printListOfPosition();
						cout << "Please Enter index: ";
						gets(userinput);
						pos = atoi(userinput);
						if ((pos >= 0) && (pos < robSys.recorded_position.size()))
							robSys.moveToPosition(robSys.recorded_position[pos]);
						break;
		    case 'h': index = strtok(NULL," ");
                      if(index!=NULL)
                        num = atoi(index);
                      else
						num = 10;
					  robSys.scanPipe(num);
					  break;
		    case 'e': index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						robSys.setExposure(atof(index));
					  }
					  else
						printf("\tMissing parameter.\n");
					  break;
		    case 'f': index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						robSys.setFrameRate(atof(index));
					  }
					  else
						printf("\tMissing parameter.\n");
					  break;
			case 'x':
				      printf("Linear scan with given waiting time\n");

       //               for(int i = 0; i<6; i++)
       //               {
       //                     index = strtok(NULL," ");
       //                     if(index!=NULL)
       //                     {
       //                         v[i] = atof(index);
       //                     }
       //               }
					  //index = strtok(NULL," ");
       //               if(index!=NULL)
						 // x = atof(index);
					  //else
						 // break;

       //               index = strtok(NULL," ");
					  //if(index!=NULL)
       //                   y = atof(index);
					  //else
						 // break;

       //               index = strtok(NULL," ");
       //               if(index!=NULL)
       //                   z = atof(index);
					  //else
						 // break;

					  //index = strtok(NULL," ");
					  //if(index!=NULL)
						 // num = atoi(index);
					  //else
						 // break;
					  //
					  //index = strtok(NULL," ");
					  //if(index!=NULL)
						 // wt = atof(index);
					  //else
						 // break;
					  
					  //v[0]=-32.5;
					  //v[1]=24.6;
					  //v[2]=16.8;
					  //v[3]=71.4;
					  //v[4]=-62.2;
					  //v[5]=-46.5;
					  //x=125.8;
					  //y=-278.8;
					  //z=381.2;

					  v[0]=37;
					  v[1]=3.5;
					  v[2]=3.7;
					  v[3]=5.2;
					  v[4]=-9.4;
					  v[5]=-9.3;
					  x=410.259;
					  y=123.1271;
					  z=594.3682;
				      num=10;
					  wt=0.1;
					  robSys.linearScan(v[0], v[1], v[2], v[3], v[4], v[5],x,y,z,num,wt);
					  break;

				case 'y':
				      printf("Dynamic Linear scan\n");
					  /*
                      for(int i = 0; i<6; i++)
                      {
                            index = strtok(NULL," ");
                            if(index!=NULL)
                            {
                                v[i] = atof(index);
                            }
                      }
					  index = strtok(NULL," ");
                      if(index!=NULL)
						  x = atof(index);
					  else
						  break;

                      index = strtok(NULL," ");
					  if(index!=NULL)
                          y = atof(index);
					  else
						  break;

                      index = strtok(NULL," ");
                      if(index!=NULL)
                          z = atof(index);
					  else
						  break;

                      index = strtok(NULL," ");
                      if(index!=NULL)
                          z = atof(index);
					  else
						  break;
					 */
					  index = strtok(NULL," ");
					  if(index!=NULL)
						  num = atoi(index);
					  else
						  break;

					 
					  v[0]=-32.5;
					  v[1]=24.6;
					  v[2]=16.8;
					  v[3]=71.4;
					  v[4]=-62.2;
					  v[5]=-46.5;
					  x=125.8;
					  y=-278.8;
					  z=381.2;
					  robSys.DynamicLinearScan(v[0], v[1], v[2], v[3], v[4], v[5],x,y,z,num);
					  break;
			case 'v': printf("\t Viewpoint Planning Scan\n");
					  index = strtok(NULL," ");
                      if(index!=NULL)
						  strcpy(filename, index);
					  else
						  break;
					  //strcpy(filename, "Outpath.csv");
					  robSys.viewpointScan(filename);
					  break;
            case 'z': printf("program terminating.\n");
                      break;
			case 't': printf("\tMultiple Scan from file\n");
					  index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						  strcpy(filename, index);
						  index = strtok(NULL," ");
						  if(index!=NULL)
								strcpy(filename2, index);
						  else
							  break;
					  }
					  else
						  break;
					  robSys.performMultipleScan(filename, filename2);
					  break;
			case 'u': printf("\tCalibration Translation Scan\n");
					  index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						  strcpy(filename, index);
						  index = strtok(NULL," ");
					  }
					  else
						  break;
					  robSys.CalibrationDataByTCPTranslate(filename);
					  break;
			case 'g': printf("\t Angular Scan\n");
					  index = strtok(NULL," ");
					  if(index!=NULL)
						degree = atoi(index);
					  else
						break;
					  index = strtok(NULL," ");
					  if(index!=NULL)
						num = atoi(index);
					  else
						break;
					  robSys.AngularScan(degree, num);
					  break;
			case 'd': printf("\t Dynamic Angular Scan\n");
					  index = strtok(NULL," ");
					  if(index!=NULL)
						degree = atoi(index);
					  else
						break;
					  index = strtok(NULL," ");
					  if(index!=NULL)
						num = atoi(index);
					  else
						break;
					  robSys.DynamicAngularScan(degree, num);
					  break;
			case 'l': printf("\t Linear Scan\n");
					  index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						  strcpy(filename, index);
						  index = strtok(NULL," ");
						  if(index!=NULL)
							num = atoi(index);
						  else
							break;
					  }
					  else
						  break;
					  robSys.multipleLinearScan(filename, num);
					  break;
			case 'b': printf("temp scan\n");
					  //robSys.moveJointTo(-38.7, 26.3, 2.2, -9.5, 61.3, 6.5);		//Orientation 1
					  //robSys.moveJointTo(-24.7, 36.8, -13.3, -18.5, 81.6, 26.5);	//Orientation 2
					  //robSys.moveJointTo(-21.0, 33.3, -2.4, -27.4, 68.8, 34.5);	//Orientation 3
					  //robSys.moveJointTo(-49.3, 4.5, 29.3, 1.1, 42.9, -90.3);		//Orientation 4
				      //robSys.moveJointTo(-34.8, 21.7, 8.0, -12.8, 61.6, 38.7);	//Orientation 5
					  //robSys.moveJointTo(-47.4, 36.2, -12.3, 0.0, 74.4, 57.4);	//Orientation 6
				      //robSys.moveJointTo(-46.2, 14.6, 17.0, -3.5, 52.9, -67.0);	//Orientation 7
				      //robSys.moveJointTo(-40.5, 26.7, 1.9, -7.1, 63.8, -17.2);	//Orientation 8
				      //robSys.moveJointTo(-39.6, 26.6, 0.6, -8.0, 66.7, -8.8);		//Orientation 9
				      //robSys.moveJointTo(-36.6, 27.4, -2.4, -10.1, 71.3, 12.2);	//Orientation 10
					  //robSys.moveJointTo(-43.9, 8.7, 22.9, 0.9, 47.8, -79.1);		//Orientation 11
					  /*
					  for(int count = 0; count <10; count++)
					  {
						 //robSys.m_robot.move(1.5,-1.5,0.1);  //4
					     robSys.m_robot.move(1.5,-1.5,1);  //4_2,7,11
						 //robSys.m_robot.move(-1.5 ,-1.5, 0.1); //2,3
						 //robSys.m_robot.move(-1.5 ,-1.5, 1); //1,5,8,9,10
						 //robSys.m_robot.move(-1.5 ,1.5, 1); //6

						 //Tested offset value
						 //1.5,1.5,1
						 //2,2,1
						 //2,1.6,1
						 //1.7,2,1
						 //2.2,1.8,0.5
						 //1.9,2.2,0.7
						 //2.3,1,0.4
						 //1,1.7,0.3

						 robSys.m_robot.updateTCP();
						 boost::this_thread::sleep(boost::posix_time::seconds(2));
						 robSys.addOnePolygon();
					  }
					  robSys.savePolygons("diagonal_scan11.csv",NULL);
					  */
					  index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						  strcpy(filename, index);
						  index = strtok(NULL," ");
						  if(index!=NULL)
							num = atoi(index);
						  else
							break;
					  }
					  else
						  break;
					  robSys.linearScan(33.4,34.5,-43.7,0.1,99.2,-0.6, 454.1, 107.7, 557.9, num);
					  robSys.savePolygons(filename, NULL);
					  break;
			case 'w': printf("robot accuracy test\n");
					  
					  index = strtok(NULL," ");
                      if(index!=NULL)
					  {
						  strcpy(filename, index);
						  index = strtok(NULL," ");
						  if(index!=NULL)
							num = atoi(index);
						  else
							break;
					  }
					  else
						  break;
					  temp[0] = robSys.recorded_position[6];
					  temp[1] = robSys.recorded_position[7];
					  temp[2] = robSys.recorded_position[8];
					  temp[3] = robSys.recorded_position[9];
					  temp[4] = robSys.recorded_position[6];

					  robSys.robotAccuracyTest(temp, filename, num);

					  break;
            default : printf("Invalid command\n");
                      break;
		}

        printf("\n");
	}while(command != 'z');

	return 0;
}

