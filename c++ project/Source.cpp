#include<iostream>
#include<string>
#include<cstdlib>
#include<math.h>
using namespace std;


bool point_in_polygon(float x , float y , float polygon_x[] , float polygon_y[] , float no){
	int count=0;
	for (int i = 0; i < no; i++)
	{
		float X;
		
		if ( (x==polygon_x[i] && y==polygon_y[i]) || (x==polygon_x[i+1] && y==polygon_y[i+1]) )
			return true;

/**		else if (polygon_y[i+1]==y)
		{
			if (polygon_y[i]==y)
			{
				if ( x>polygon_x[i] && x<polygon_x[i+1] )
				{
					float slope=(polygon_y[i]-polygon_y[i+1])/(polygon_x[i]-polygon_x[i+1]);
			        X=polygon_x[i]+((y-polygon_y[i])/slope);
			        if (X<x)
				        return true;
				}
			}
		}
		**/
		else if ( (y>polygon_y[i] && y<polygon_y[i+1]) || (y<polygon_y[i] && y>polygon_y[i+1]) )
		{
			float slope=(polygon_y[i]-polygon_y[i+1])/(polygon_x[i]-polygon_x[i+1]);
			X=polygon_x[i]+((y-polygon_y[i])/slope);
			if (X>x)
				count++;
			else if (X==x)
				return true;
		}
		else if (polygon_y[i+1]==y)
		{
			if (polygon_y[i]==y)
			{
				if ( (x>polygon_x[i+1] && x<polygon_x[i+1]) || (x<polygon_x[i] && x>polygon_x[i+1]))
				        return true;
				
			}
			else if (polygon_x[i+1]>x && polygon_y[i]<y) 
				count++;
		}
		else if (polygon_y[i]==y)
		{
			if (polygon_x[i]>x && polygon_y[i+1]<y)
				count++;
		}
	}
		if (count % 2  != 0)
			return true;   //  in polygon
		else
			return false;  //  out polygon
	}






int main(){
	string input;   //  input string
	string operation;  //  operation string
	cout<<"polygons data...seprated between each other';'"<<endl<<"polygons="; 
	getline(cin,input);
	int n=input.length();  //  n: length of string
//***********
	int no_polygon_points[100][1];    //  no of points in each polygon 'use in operations'
	int a=0,x=0,y=0;    //  a: number of semi column but now its no of polygons ,,  x: counter of x in 'point_x'  ,,  y: counter of y in 'point_y'
	string point_x[100][100];     //  'x' in all polygons "string data type"
	string point_y[100][100];     //  'y' in all polygons "string data type"
	float polygon_point_x[100][100];    //  'x' in all polygons...each polygon has row
	float polygon_point_y[100][100];    //  'y' in all polygons...each polygon has row
	int open_bra,close_bra,comma;  //  places of '('   ')'   ','
	for (int i = 0; i < n; i++)
	{
	     if ( input[i] == '(')
	     {
			 open_bra=i;
	     }	
		 if ( input[i] == ',')
	     {
			 comma=i;
			 point_x[a][x] = input.substr(open_bra +1 , comma -open_bra -1);   //  a: polygon   ,,,   x: 'x' in polygon
			 polygon_point_x[a][x]= atof(point_x[a][x].c_str());   // convert point to float 
			 x++;  // add 1 for 'x' to next input x coordinate
	     }	
		 if ( input[i] == ')')
	     {
			 close_bra=i;
			 point_y[a][y] = input.substr(comma +1 , close_bra -comma -1);   //  a: polygon   ,,,   y: 'y' in polygon	
			 polygon_point_y[a][y]= atof(point_y[a][y].c_str());   // convert point to float 
			 y++;  // add 1 for 'y' to next input y coordinate
			 no_polygon_points[a][0]=y;
			 if (input[i+1] == ',')  // to pass ',' which between two points
				 i++;
			 if (input[i+1] == ';')  // to be in next polygon
				 a++,x=0,y=0,i++;	 
	     }	
	}
	a++;  // add "1" to 'a' because no of polygons is 'a+1'

	int Total_Number_Points=0;  
	for (int i = 0; i < a; i++)  //  use in op 2
	{
		Total_Number_Points+= no_polygon_points[i][0];
	}
//	cout<<Total_Number_Points<<" ";
//	cout<<a<<" "<<no_polygon_points[2][0]<<" ";
	float polygon_x[100][100];    //  'x' in all polygons...with red
	float polygon_y[100][100];    //  'y' in all polygons...with red
	int no_points[100][1];
	for (int i = 0; i < a; i++)   //  copy polygons for ops in level 2
	{	for (int z = 0; z < no_polygon_points[i][0]; z++)
		{
			polygon_x[i][z]=polygon_point_x[i][z];
			polygon_y[i][z]=polygon_point_y[i][z];
		}
	    no_points[i][0]=no_polygon_points[i][0];
	}
//*****   redundant
	int redundant=0;   // no of redundant point
	for (int i = 0; i < a; i++)  //  repeated point
	{
		int count=0;  //  counter for new data in polygon_point_x
		for (int x = 0; x < no_polygon_points[i][0]; x++)  
		{
			if (polygon_point_x[i][x]==polygon_point_x[i][x+1] && polygon_point_y[i][x]==polygon_point_y[i][x+1])
			    {
					redundant++;
//					 cout<<polygon_point_x[i][x+1]<<" "<<polygon_point_y[i][x+1]<<endl;
			    }			
			else
			{
				polygon_point_x[i][count]=polygon_point_x[i][x];  //  x in each polygon except repeated point
				polygon_point_y[i][count]=polygon_point_y[i][x];  //  y in each polygon except repeated point
				count++;
			}
		}
		no_polygon_points[i][0]=count;  //   after clear repeated point
	}//cout<<endl;
//******
	for (int i = 0; i < a; i++)  //  points on straight line
	{
		for (int x = 0,y=0; y < no_polygon_points[i][0]-2; y++)
		{

			float slope1=(polygon_point_y[i][x]-polygon_point_y[i][x+1])/(polygon_point_x[i][x]-polygon_point_x[i][x+1]);
			float slope2=(polygon_point_y[i][x]-polygon_point_y[i][x+2])/(polygon_point_x[i][x]-polygon_point_x[i][x+2]);
			if ( slope1==slope2 && x+1<=no_polygon_points[i][0] && x+2<=no_polygon_points[i][0] )
				{  
					redundant++;
//					cout<<polygon_point_x[i][x+1]<<","<<polygon_point_y[i][x+1]<<endl;
//					no_polygon_points[i][0]--;
					for (int d = 0; d < no_polygon_points[i][0]; d++)
					{
						if (d==x+1)
						{
							for (int k = x+1; k < no_polygon_points[i][0]-1; k++)
							{
								polygon_point_x[i][k]=polygon_point_x[i][k+1];
						        polygon_point_y[i][k]=polygon_point_y[i][k+1];
							}
							no_polygon_points[i][0]--;
							y=-1;
							x=0;
					        break;    
						}	
					}
			    }
			else
			  x++;
		}
	}
//***** 
	for (int i = 0; i < a; i++)  //  start and end is the same point
	{
		int x=no_polygon_points[i][0];
		if (polygon_point_x[i][0]==polygon_point_x[i][x-1] &&
			polygon_point_y[i][0]==polygon_point_y[i][x-1])
		{
			redundant++;
//			cout<<polygon_point_x[i][x-1]<<","<<polygon_point_y[i][x-1]<<endl;
			no_polygon_points[i][0]--;
		}
	}
//*****
	for (int i = 0; i < a; i++)  //  first point and last two points on straight line
	{
		int x=no_polygon_points[i][0];
		if (x-2 == 0)
			break;
		float slope1=(polygon_point_y[i][0]-polygon_point_y[i][x-1])/(polygon_point_x[i][0]-polygon_point_x[i][x-1]);
		float slope2=(polygon_point_y[i][0]-polygon_point_y[i][x-2])/(polygon_point_x[i][0]-polygon_point_x[i][x-2]);
		if (slope1==slope2)
		{
			redundant++;
//			cout<<polygon_point_x[i][x-1]<<","<<polygon_point_y[i][x-1]<<endl;
			no_polygon_points[i][0]--;
		}
	}
//*****
	for (int i = 0; i < a; i++)  //  last point and first two points on straight line
	{
		int x=no_polygon_points[i][0];
		if (x-2 == 0)
			break;
		float slope1=(polygon_point_y[i][0]-polygon_point_y[i][1])/(polygon_point_x[i][0]-polygon_point_x[i][1]);
		float slope2=(polygon_point_y[i][0]-polygon_point_y[i][x-1])/(polygon_point_x[i][0]-polygon_point_x[i][x-1]);
		if (slope1==slope2)
		{
			redundant++;
//			cout<<polygon_point_x[i][0]<<","<<polygon_point_y[i][0]<<endl;
			no_polygon_points[i][0]--;
			for (int x = 0; x < no_polygon_points[i][0]; x++)
			{
				polygon_point_x[i][x]=polygon_point_x[i][x+1];
			    polygon_point_y[i][x]=polygon_point_y[i][x+1];
			}
		}
	}
//	cout<<redundant<<endl;
/**	for (int i = 0; i < a; i++)
	{
		for (int x = 0; x < no_polygon_points[i][0]; x++)
		{
			cout<<polygon_point_x[i][x]<<","<<polygon_point_y[i][x]<<" ";
		}
		cout<<endl;
	}**/

//      (1,1),(2,2),(3,3),(3,3),(6,6),(1,1)   (1,1),(5,5),(6,5),(2,12),(9,9)
//******************************************************************************** operatin
	int Quit=1;
	do
	{			
	getline(cin,operation);
//1	          a: no of polygon calculated Previously
	if (operation == "Number_Polygons")
	{
		if (Total_Number_Points <= 2)		
			cout<<"none"<<endl;	
		else
			cout<<a<<endl;			} 
//2           Total_Number_Points: calculated Previously when we store x in polygon_point_x
	if (operation == "Total_Number_Points")
	{
		if (Total_Number_Points == 0)		
			cout<<"none"<<endl;		
		else
			cout<<Total_Number_Points<<endl;    	}
//3

	if (operation == "Minimum_X")
	{
		float min_x = polygon_point_x[0][0];
		for (int i = 0; i < a; i++)		
			for (int x = 0; x < no_polygon_points[i][0]; x++)	    
				if (polygon_point_x[i][x] < min_x )			    
					min_x =  polygon_point_x[i][x];
		if (Total_Number_Points == 0)		
			cout<<"none"<<endl;		
		else
			cout<<min_x<<endl;		}
//4
	if (operation == "Maximum_X")
	{
		float max_x = polygon_point_x[0][0];
		for (int i = 0; i < a; i++)		
			for (int x = 0; x < no_polygon_points[i][0]; x++)		    
				if (polygon_point_x[i][x] > max_x  )
					max_x =  polygon_point_x[i][x];	
		if (Total_Number_Points == 0)		
			cout<<"none"<<endl;		
		else
			cout<<max_x<<endl;		}
//5
	if (operation == "Minimum_Y")
	{
		float min_y = polygon_point_y[0][0];
		for (int i = 0; i < a; i++)
			for (int x = 0; x < no_polygon_points[i][0]; x++)		    
				if (polygon_point_y[i][x] < min_y  )			    
					min_y =  polygon_point_y[i][x];
		if (Total_Number_Points == 0)		
			cout<<"none"<<endl;		
		else
			cout<<min_y<<endl;		}
//6
	if (operation == "Maximum_Y")
	{
		float max_y = polygon_point_y[0][0];
		for (int i = 0; i < a; i++)
			for (int x = 0; x < no_polygon_points[i][0]; x++)
				if (polygon_point_y[i][x] > max_y  )			    
					max_y =  polygon_point_y[i][x];	
		if (Total_Number_Points == 0)		
			cout<<"none"<<endl;		
		else
			cout<<max_y<<endl;		}
//7            æÌÈÊ äÞØ ÇáãÓÊØíá  max,min æÍØíÊå ÚáÔÇä ÇÚÑÝ operation(3,4,5,6) ÌÈÊ Çááì Ìæå
	if (operation == "Enclosing_Rectangle")
	{
		float min_x = polygon_point_x[0][0];
		for (int i = 0; i < a; i++)		
			for (int x = 0; x < no_polygon_points[i][0]; x++)	    
				if (polygon_point_x[i][x] < min_x  )			    
					min_x =  polygon_point_x[i][x];
		float max_x = polygon_point_x[0][0];
		for (int i = 0; i < a; i++)		
			for (int x = 0; x < no_polygon_points[i][0]; x++)		    
				if (polygon_point_x[i][x] > max_x  )
					max_x =  polygon_point_x[i][x];	
		float min_y = polygon_point_y[0][0];
		for (int i = 0; i < a; i++)
			for (int x = 0; x < no_polygon_points[i][0]; x++)		    
				if (polygon_point_y[i][x] < min_y  )			    
					min_y =  polygon_point_y[i][x];
		float max_y = polygon_point_y[0][0];
		for (int i = 0; i < a; i++)
			for (int x = 0; x < no_polygon_points[i][0]; x++)
				if (polygon_point_y[i][x] > max_y )			    
					max_y =  polygon_point_y[i][x];	
		float x1 = min_x , y1 = max_y , x3 = max_x , y3 = min_y;  // point 1,3
		float x2 = x1 , y2 = y3;  // point 2 
		float x4 = x3 , y4 = y1;  // point 4
		if (Total_Number_Points == 0)		
			cout<<"none"<<endl;		
		else
		cout<<"("<<x1<<","<<y1<<")"<<","<<"("<<x2<<","<<y2<<")"<<","<<"("<<x3<<","<<y3<<")"<<","<<"("<<x4<<","<<y4<<")"<<endl;	}	
//8
	if (operation == "Total_Redundant_Points")
	{
		if (redundant==0)
			cout<<"none"<<endl;
		else
			{
				if (redundant==0)
					cout<<"none";
				else
					cout<<redundant<<endl;
		    }
	}	
//9
	if (operation == "Quit")
	{
		Quit=0; 	}
//10
	string op = operation.substr(0,14);   
	if (op == "Polygon_Points")
	{
		int deg;  //   deg: no of degree in 
		string degree =operation.substr(15,4);
		deg = atof(degree.c_str());
		int no = no_polygon_points[deg -1][0];   // ãÊÚÑÝå ÝæÞ æÈÊÌíÈáì ÚÏÏ ÇáäÞØ Çááì Ýì ÇáãÖáÚ Çááì ÚÇíÒå
		bool comma= false ;
		if (Total_Number_Points == 0 || deg > a || deg <= 0 )	 // if input no > polygons no print none 
			cout<<"none"<<endl;	
		else
		{			
			for (int i = 0; i < no ; i++)  //print points in this poligon
			{
				if (comma)
					cout<<",";
				cout<<"("<<polygon_point_x[deg -1][i] <<","<<polygon_point_y[deg -1][i] <<")" ;
				comma=true;
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}    
	}
//11
    op = operation.substr(0,14); 
	if (op == "Point_Polygons")
	{
		int sign1 = operation.find(",") , sign2 = operation.find(")");  // know places for this signs
		string point_x = operation.substr(16,sign1 -16);  //  x in the the input point
		float x = atof(point_x.c_str());
		string point_y = operation.substr(sign1 +1,sign2 - sign1 -1 );  //  y in the the input point
		float y = atof(point_y.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < a; i++)  // to find degrees of polygons which have this point
			for (int j = 0; j < no_points [i][0]; j++)
				if (x == polygon_x[i][j] && y == polygon_y[i][j])  // see if input point equal polygon point
			    {
					if (comma)
						cout<<",";
					cout<<i+1;  // print the degree of true polygon
					comma=true;
			    }
				if (!comma)
					cout<<"none";
		cout<<endl;
		}
	}	
//12  
	op = operation.substr(0,25);
	if (op == "List_Polygons_Points More")
	{
		int no_points;  //   input no 
		string no =operation.substr(26,4);  //  input no in string data type 
		no_points = atof(no.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < a; i++)
			    if (no_polygon_points [i][0] > no_points )
				{	
					if (comma)
						cout<<",";
				    cout<<i+1;
					comma=true;
				}
			if(!comma)
				cout<<"none";
		cout<<endl;
		}
	}
//13
	op = operation.substr(0,25);
	if (op == "List_Polygons_Points Less")
	{
		int no_points;  //   input no 
		string no =operation.substr(26,4);  //  input no in string data type 
		no_points = atof(no.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < a; i++)	
			    if (no_polygon_points [i][0] < no_points )
				{
					if (comma)
						cout<<",";
				    cout<<i+1;
					comma=true;
				}
			if (!comma)
				cout<<"none";
		    cout<<endl;
		}
	}
//14
	op = operation.substr(0,26);
	if (op == "List_Polygons_Points Equal")
	{
		int no_points;  //   input no 
		string no =operation.substr(27,4);  //  input no in string data type 
		no_points = atof(no.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else 
		{
			for (int i = 0; i < a; i++)	
			    if (no_polygon_points [i][0] == no_points )
				{
					if (comma)
						cout<<",";
				    cout<<i+1;
					comma=true;
				}
			if (!comma)
				cout<<"none";
		    cout<<endl;
		}	
	}
//15
	op = operation.substr(0,25);
	if (op == "List_Points_Polygons More")
	{
		float arr_points[200];
		int no_polygons, counter=1, b=0,c=0  ; 
		string no =operation.substr(26,4);  //  input no in string data type 
		no_polygons = atof(no.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			float arr_points[200];
			int q=0;
			for (int i = 0; i < a; i++)
		        {
			       for (int x = 0; x < no_points [i][0]; x++)
			       {
				       if (c==i && x==b)				          
					          continue;		
				       if (polygon_x[c][b]==polygon_x[i][x] &&
				           polygon_y[c][b]==polygon_y[i][x])				          
					         counter++;	 
			      }
			      if (i==a-1)
			         {
				        if (counter>no_polygons)				           
					    {    
							arr_points[q]=polygon_x[c][b];
							arr_points[q+1]=polygon_y[c][b];q+=2;
						}
				        i=-1,b++;counter=1;
				        if (b==no_points [c][0])
					           b=0,c++;
						if (c==a)
							break;
			         }
		         }
			int x=0;
			for (int i = x+2; i < q; i+=2)  // to print number for one time
			{
				if (arr_points[x] == arr_points[i] && arr_points[x+1] == arr_points[i+1])
		           {
			           q-=2,i-=2;;
			           for (int z=i+2 ; z < q; z+=2)
					   {
				       arr_points[z]=arr_points[z+2];
					   arr_points[z+1]=arr_points[z+3];
					   }
				   }
				if (i == q-2)
		           {
			           x+=2;
			           i=x;
		           }
			}
			for (int i = 0; i < q; i+=2)
			{
				if (comma)
					cout<<",";
				cout<<"("<<arr_points[i]<<","<<arr_points[i+1]<<")";
				comma=true;
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//16
	op = operation.substr(0,25);
	if (op == "List_Points_Polygons Less")
	{
		float arr_points[200];
		int no_polygons, counter=1, b=0,c=0  ; 
		string no =operation.substr(26,4);  //  input no in string data type 
		no_polygons = atof(no.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			float arr_points[200];
			int q=0;
			for (int i = 0; i < a; i++)
		        {
			       for (int x = 0; x < no_points [i][0]; x++)
			       {
				       if (c==i && x==b)				          
					          continue;		
				       if (polygon_x[c][b]==polygon_x[i][x] &&
				           polygon_y[c][b]==polygon_y[i][x])				          
					         counter++;	 
			      }
			      if (i==a-1)
			         {
				        if (counter<no_polygons)				           
					    {    
							arr_points[q]=polygon_x[c][b];
							arr_points[q+1]=polygon_y[c][b];q+=2;
						}
				        i=-1,b++;counter=1;
				        if (b==no_points [c][0])
					           b=0,c++;
						if (c==a)
							break;
			         }
		         }
			int x=0;
			for (int i = x+2; i < q; i+=2)  // to print number for one time
			{
				if (arr_points[x] == arr_points[i] && arr_points[x+1] == arr_points[i+1])
		           {
			           q-=2,i-=2;;
			           for (int z=i+2 ; z < q; z+=2)
					   {
				       arr_points[z]=arr_points[z+2];
					   arr_points[z+1]=arr_points[z+3];
					   }
				   }
				if (i == q-2)
		           {
			           x+=2;
			           i=x;
		           }
			}
			for (int i = 0; i < q; i+=2)
			{
				if (comma)
					cout<<",";
				cout<<"("<<arr_points[i]<<","<<arr_points[i+1]<<")";
				comma=true;
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//17
	op = operation.substr(0,26);
	if (op == "List_Points_Polygons Equal")
	{
		float arr_points[200];
		int no_polygons, counter=1, b=0,c=0  ; 
		string no =operation.substr(27,4);  //  input no in string data type 
		no_polygons = atof(no.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			float arr_points[200];
			int q=0;
			for (int i = 0; i < a; i++)
		        {
			       for (int x = 0; x < no_points [i][0]; x++)
			       {
				       if (c==i && x==b)				          
					          continue;		
				       if (polygon_x[c][b]==polygon_x[i][x] &&
				           polygon_y[c][b]==polygon_y[i][x])				          
					         counter++;	 
			      }
			      if (i==a-1)
			         {
				        if (counter==no_polygons)				           
					    {    
							arr_points[q]=polygon_x[c][b];
							arr_points[q+1]=polygon_y[c][b];q+=2;
						}
				        i=-1,b++;counter=1;
				        if (b==no_points [c][0])
					           b=0,c++;
						if (c==a)
							break;
			         }
		         }
			int x=0;
			for (int i = x+2; i < q; i+=2)  // to print number for one time
			{
				if (arr_points[x] == arr_points[i] && arr_points[x+1] == arr_points[i+1])
		           {
			           q-=2,i-=2;;
			           for (int z=i+2 ; z < q; z+=2)
					   {
				       arr_points[z]=arr_points[z+2];
					   arr_points[z+1]=arr_points[z+3];
					   }
				   }
				if (i == q-2)
		           {
			           x+=2;
			           i=x;
		           }
			}
			for (int i = 0; i < q; i+=2)
			{
				if (comma)
					cout<<",";
				cout<<"("<<arr_points[i]<<","<<arr_points[i+1]<<")";
				comma=true;
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//18
	op= operation.substr(0,17);
	if (op == "Polygon_Perimeter")
	{
		int d;
		float distance=0;
		string no =operation.substr(18,4);
		d= atof(no.c_str());
		d--;    //  array start from zero 
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int x = 0; x < no_polygon_points [d][0]-1; x++)
				{
					distance+=sqrt( pow(polygon_point_y[d][x]-polygon_point_y[d][x+1],2) + 
						            pow(polygon_point_x[d][x]-polygon_point_x[d][x+1],2) );
				}							
			distance+=sqrt( pow(polygon_point_y[d][0]-polygon_point_y[d][no_polygon_points [d][0]-1],2) + 
				            pow(polygon_point_x[d][0]-polygon_point_x[d][no_polygon_points [d][0]-1],2) );
			cout<<distance<<endl;
		}
	}
//19
	op= operation.substr(0,14);
	if (op == "List_Triangles")
	{
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < a; i++)
		        {
			        if (no_polygon_points [i][0] == 3)
				        {
							if (comma)
					            cout<<",";
							cout<<i+1;
							comma=true;
					    }
		        }
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//20
	op= operation.substr(0,15);
	if (op == "List_Rectangles")
	{
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < a; i++)
			{
				if (no_polygon_points [i][0] == 4)
				{
					float slope1=(polygon_point_y[i][0]-polygon_point_y[i][1])/(polygon_point_x[i][0]-polygon_point_x[i][1]);
					float slope2=(polygon_point_y[i][1]-polygon_point_y[i][2])/(polygon_point_x[i][1]-polygon_point_x[i][2]);
					float slope3=(polygon_point_y[i][3]-polygon_point_y[i][2])/(polygon_point_x[i][3]-polygon_point_x[i][2]);
					float slope4=(polygon_point_y[i][0]-polygon_point_y[i][3])/(polygon_point_x[i][0]-polygon_point_x[i][3]);
					if ( slope1==slope3 && slope2==slope4 )
						if ( (slope1==(-1/slope2) && slope3==(-1/slope4)) )
						   {
							   if (comma)
					            cout<<",";
							   cout<<i+1;
							   comma=true;
					       }
				}
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//21
	op= operation.substr(0,14);
	if (op == "List_Trapezoid")
	{
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < a; i++)
			{
				if (no_polygon_points [i][0] == 4)
				{
					float slope1=(polygon_point_y[i][0]-polygon_point_y[i][1])/(polygon_point_x[i][0]-polygon_point_x[i][1]);
					float slope2=(polygon_point_y[i][1]-polygon_point_y[i][2])/(polygon_point_x[i][1]-polygon_point_x[i][2]);
					float slope3=(polygon_point_y[i][3]-polygon_point_y[i][2])/(polygon_point_x[i][3]-polygon_point_x[i][2]);
					float slope4=(polygon_point_y[i][0]-polygon_point_y[i][3])/(polygon_point_x[i][0]-polygon_point_x[i][3]);
					if ( (slope1==slope3 && slope2!=slope4) || (slope2==slope4 && slope1!=slope3) )
					{
						if (comma)
					        cout<<",";
						cout<<i+1;
						comma=true;
					}
				}
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//22
	op= operation.substr(0,16);
	if (op == "Inside_Rectangle")
	{
		string rec[8];
		float rect[8];
		int x=0,l=operation.length();
		bool cma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 17; i < l; i++)
		    {
			    if ( operation[i] == '(')
			           open_bra=i;
		        if ( operation[i] == ',')
	               {
			           comma=i;
					   rec[x] = operation.substr(open_bra +1 , comma -open_bra -1);   
			           rect[x]= atof(rec[x].c_str());   // convert point to float 
			           x++;  
	               }
			    if ( operation[i] == ')')
	               {
			           close_bra=i;
					   rec[x] = operation.substr(comma +1 , close_bra -comma -1);   
			           rect[x]= atof(rec[x].c_str());   
			           x++,i++;  
	               }
		    }		
		    float min_x=rect[0], max_x=rect[0], min_y=rect[1], max_y=rect[1] ;
		    for (int i = 0; i < 8; i+=2)
		    {
			    if (rect[i]<min_x)
					min_x=rect[i];
			    if (rect[i]>max_x)
				    max_x=rect[i];
		    }
		    for (int i = 1; i < 8; i+=2)
		    {
			    if (rect[i]<min_y)		
				    min_y=rect[i];
			    if (rect[i]>max_y)
				    max_y=rect[i];
		    }
		    for (int i = 0; i < a; i++)
		    {
			    int check=0;
			    do
			    {
				    for (int x = 0; x < no_polygon_points [i][0]; x++)
			        {
			 	        if ( polygon_point_x[i][x]<min_x || polygon_point_x[i][x]>max_x || polygon_point_y[i][x]<min_y || polygon_point_y[i][x]>max_y )
			 		        check=1;
			 			if ( x==no_polygon_points [i][0]-1 && check==0 )
			 			   {
							   if (cma)
					               cout<<",";
			 				   cout<<i+1;
							   cma=true;
			 				   check=1;
			 			   }
			        }
			    } while (check==0);
			 
		    }
			if (!cma)
				cout<<"none";
			cout<<endl;
		}	
	}
//23
	op= operation.substr(0,13);
	if (op == "Inside_Circle")
	{		
		int l=operation.length();
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			int sign1 = operation.find(",") , sign2 = operation.find(")");  // know places for this signs
		    string point_x = operation.substr(15 , sign1 -15);  //  x in center
		    float X = atof(point_x.c_str());
		    string point_y = operation.substr(sign1 +1 , sign2 - sign1 -1);  //  y in center
		    float Y = atof(point_y.c_str());
			string red = operation.substr(sign2 +2 , l -sign2 -2);
		    float r = atof(red.c_str());
			for (int i = 0; i < a; i++)
			{
				for (int x = 0; x < no_polygon_points [i][0]; x++)
				{
					float distance=sqrt( pow(Y-polygon_point_y[i][x],2) + 
				                         pow(X-polygon_point_x[i][x],2) );
					if (distance > r)
						break;
					if (x == no_polygon_points [i][0]-1)
					{
						if (comma)
					        cout<<",";
						cout<<i+1;
						comma=true;
					}
				}
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
	    }	
	}
//24
	op= operation.substr(0,12);
	if (op == "Polygon_Area")
	{
		int d;
		float y=0,x=0,area;
		string no =operation.substr(13,4);
		d= atof(no.c_str());
		d--;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			for (int i = 0; i < no_polygon_points [d][0]-1; i++)
		        {
			        y+=polygon_point_y[d][i]*polygon_point_x[d][i+1];
			        x+=polygon_point_x[d][i]*polygon_point_y[d][i+1];
		        }
		    y+=polygon_point_y[d][no_polygon_points [d][0]-1]*polygon_point_x[d][0];
		    x+=polygon_point_x[d][no_polygon_points [d][0]-1]*polygon_point_y[d][0];
		    area=(y-x)/2;
			if (area<0)
				area*=-1;
		    cout<<area<<endl;
		}	
	}
//25
	op= operation.substr(0,19);
	if (op == "Polygons_Area_Range")
	{
		int sign1 = operation.find(",");
		int l=operation.length();
		float X=0,Y=0;
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			string  minm = operation.substr(20 , sign1 -20);
			float area,min = atof(minm.c_str());
			string  maxm = operation.substr(sign1+1 , l -sign1 -1 );
			float max = atof(maxm.c_str());
			for (int i = 0; i < a; i++)
			{
				for (int x = 0; x < no_polygon_points [i][0]-1; x++)
		        {
			        Y+=polygon_point_y[i][x]*polygon_point_x[i][x+1];
			        X+=polygon_point_x[i][x]*polygon_point_y[i][x+1];
		        }
		        Y+=polygon_point_y[i][no_polygon_points [i][0]-1]*polygon_point_x[i][0];
		        X+=polygon_point_x[i][no_polygon_points [i][0]-1]*polygon_point_y[i][0];
		        area=(Y-X)/2;
			    if (area<0)
				    area*=-1;
				if (area>=min && area<=max)
					{
						if (comma)
					        cout<<",";
						cout<<i+1;
						comma= true ;
				    }
				area=0;
				X=0;Y=0;
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
//26
	op= operation.substr(0,24);
	if (op == "Polygons_Enclosing_Point")
	{
		int sign1 = operation.find(",") , sign2 = operation.find(")");  // know places for this signs
		string point_x = operation.substr(26,sign1 -26);  //  x in op
		float x = atof(point_x.c_str());
		string point_y = operation.substr(sign1 +1,sign2 - sign1 -1 );  //  y in op
		float y = atof(point_y.c_str());
		bool comma= false ;
		if (Total_Number_Points == 0)
			cout<<"none"<<endl;
		else
		{
			float pol_x[100];
			float pol_y[100];
			for (int i = 0; i < a; i++)
			{
				for (int x = 0; x < no_polygon_points [i][0]; x++)
				{
					pol_x[x]=polygon_point_x[i][x];
				    pol_y[x]=polygon_point_y[i][x];
				}
				if ( point_in_polygon(x,y,pol_x,pol_y,no_polygon_points [i][0]) )
					{
						if (comma)
					        cout<<",";
						cout<<i+1;
						comma=true;
			        }
			}
			if (!comma)
				cout<<"none";
			cout<<endl;
		}
	}
	

} while (Quit==1); 


return 0;
}