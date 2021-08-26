#include<iostream>
#include<cmath>
#include<stdlib.h>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;


class Qube{
    
    public:
        Qube(){ //constructor    
        n = 51; 
        centar = (n-1)/2;
        //FIELD MATRIX
        for(int i = 0;i<n;i++){
            array[i] = new char[n];
        }
        //VERTIXES OF CUBE  
        for(int i = 0; i<8; i++){
            vertex_points[i] = new int[3];
        }
        //POINTS IN CUBE
        for(int i=0;i<300;i++){
            cube_points[i] = new int[4];
        }

        this->create_cube();
        }

        ~Qube(){
            //DELETE DINAMICLY ALLOCATED MEMORY
            for(int j = 0;j<n;j++){
                delete [] array[j]; 
            }
            for(int i = 0; i<8; i++){
            delete [] vertex_points[i];
            }
            for(int i=0;i<300;i++){
            delete [] cube_points[i];
        }
        }
   
        void Printvertex_points(){
            for(int i=0;i<8;i++){
                for(int j=0;j<3;j++){
                    cout<<vertex_points[i][j]<<" ";
                }
                cout<<endl;
            }
        }
 
        void Rotate(double angle_x,double angle_y,double angle_z){
            
            int buffer_x; int buffer_y; int buffer_z;
            angle_x = (angle_x*M_PI)/180;
            angle_y = (angle_y*M_PI)/180;
            angle_z = (angle_z*M_PI)/180;
           
            for(int i = 0; i<300; i++)
            {
                // rotate around x axis
                buffer_x = cube_points[i][0] ; 
                buffer_y = round(cos(angle_x)*cube_points[i][1]-sin(angle_x)*cube_points[i][2]);
                buffer_z = round(sin(angle_x)*cube_points[i][1] + cos(angle_x)*cube_points[i][2]);
                
                cube_points[i][0]=buffer_x;
                cube_points[i][1]=buffer_y;
                cube_points[i][2]=buffer_z;

                //rotate vertixes
                if(i<8){
                    buffer_x = vertex_points[i][0] ; 
                    buffer_y = round(cos(angle_x)*vertex_points[i][1]-sin(angle_x)*vertex_points[i][2]);
                    buffer_z = round(sin(angle_x)*vertex_points[i][1] + cos(angle_x)*vertex_points[i][2]);
                    
                    vertex_points[i][0]=buffer_x;
                    vertex_points[i][1]=buffer_y;
                    vertex_points[i][2]=buffer_z;
                }

                // rotate around y axis
                buffer_x = round(sin(angle_y)*cube_points[i][2] + cos(angle_y)*cube_points[i][0]); 
                buffer_y = cube_points[i][1] ; 
                buffer_z = round(cos(angle_y)*cube_points[i][2]-sin(angle_y)*cube_points[i][0]);

                cube_points[i][0]=buffer_x;
                cube_points[i][1]=buffer_y;
                cube_points[i][2]=buffer_z;

                //rotate vertixes
                if(i<8){
                    buffer_x = round(sin(angle_y)*vertex_points[i][2] + cos(angle_y)*vertex_points[i][0]); 
                    buffer_y = vertex_points[i][1] ; 
                    buffer_z = round(cos(angle_y)*vertex_points[i][2]-sin(angle_y)*vertex_points[i][0]);

                    
                    vertex_points[i][0]=buffer_x;
                    vertex_points[i][1]=buffer_y;
                    vertex_points[i][2]=buffer_z;
                }

                // rotate around z axis
                buffer_x = round(cos(angle_z)*cube_points[i][0]-sin(angle_z)*cube_points[i][1]); 
                buffer_y = round(sin(angle_z)*cube_points[i][0]+cos(angle_z)*cube_points[i][1]);
                buffer_z = cube_points[i][2];

                cube_points[i][0]=buffer_x;
                cube_points[i][1]=buffer_y;
                cube_points[i][2]=buffer_z;

                //rotate vertixes
                if(i<8){
                    buffer_x = round(cos(angle_z)*vertex_points[i][0]-sin(angle_z)*vertex_points[i][1]); 
                    buffer_y = round(sin(angle_z)*vertex_points[i][0]+cos(angle_z)*vertex_points[i][1]);
                    buffer_z = vertex_points[i][2];
                    
                    vertex_points[i][0]=buffer_x;
                    vertex_points[i][1]=buffer_y;
                    vertex_points[i][2]=buffer_z;
                }

            }
            this->load_cube();
        }
      
        void Print(){
            for(int i = 0; i<n; i++){
                for(int j = 0; j<n; j++){
                    cout<< *(*(array+i)+j)<< " "; 
                }
                cout<< endl;
            }
        }
        
        void GetEdge(int v){
            for(int i=0;i<300;i++){
                if(cube_points[i][3]==v){
                    cout<<"x: "<<cube_points[i][0]<<" y: "<<cube_points[i][1]<<" z: "<<cube_points[i][2]<<endl;
                }
            }
        }


    private:
        int n;
        int centar; 
        int *vertex_points[8];
        int *cube_points[300];
        char *array[51];
        

        void create_cube(){             
            int sign;
            int sign_x;
            int sign_y = 1;
            int sign_z = 1;
            // implementation of a 'binary counter' to load the cordinates
            // why spend 3 min handwriting coordinates when you can spend 20 min creating an algorithm that does the same thing :'(
            for(int i = 0; i<8;i++){ 
                if (sign_x == -1){
                        sign_y = -sign_y;
                    }
                for(int j = 0; j<3; j++){
                    if (i%2 == 0){
                        sign_x = 1;
                    }else{
                        sign_x = -1;
                    }
                    if (i>3){
                        sign_z = -1;
                    }
                    if(j == 0){
                        sign = sign_x;
                    }else if(j == 1){
                        sign = sign_y;
                    }else if (j == 2){
                        sign = sign_z;
                    }
                    vertex_points[i][j] = (centar-1)/2 * sign; 
                }
            }
            //define a matrix with connection vertex_points of the cube (x1,y1,x2,y2,z1,z2)
            int edges_matrix [12][6] = {{vertex_points[1][0],vertex_points[1][1],vertex_points[3][0],vertex_points[3][1],vertex_points[1][2],vertex_points[3][2]},
                                        {vertex_points[1][0],vertex_points[1][1],vertex_points[5][0],vertex_points[5][1],vertex_points[1][2],vertex_points[5][2]},
                                        {vertex_points[1][0],vertex_points[1][1],vertex_points[0][0],vertex_points[0][1],vertex_points[1][2],vertex_points[0][2]},
                                        {vertex_points[2][0],vertex_points[2][1],vertex_points[3][0],vertex_points[3][1],vertex_points[2][2],vertex_points[3][2]},
                                        {vertex_points[2][0],vertex_points[2][1],vertex_points[6][0],vertex_points[6][1],vertex_points[2][2],vertex_points[6][2]},
                                        {vertex_points[2][0],vertex_points[2][1],vertex_points[0][0],vertex_points[0][1],vertex_points[2][2],vertex_points[0][2]},
                                        {vertex_points[4][0],vertex_points[4][1],vertex_points[5][0],vertex_points[5][1],vertex_points[4][2],vertex_points[5][2]},
                                        {vertex_points[4][0],vertex_points[4][1],vertex_points[6][0],vertex_points[6][1],vertex_points[4][2],vertex_points[6][2]},
                                        {vertex_points[4][0],vertex_points[4][1],vertex_points[0][0],vertex_points[0][1],vertex_points[4][2],vertex_points[0][2]},
                                        {vertex_points[7][0],vertex_points[7][1],vertex_points[3][0],vertex_points[3][1],vertex_points[7][2],vertex_points[3][2]},
                                        {vertex_points[7][0],vertex_points[7][1],vertex_points[5][0],vertex_points[5][1],vertex_points[7][2],vertex_points[5][2]},
                                        {vertex_points[7][0],vertex_points[7][1],vertex_points[6][0],vertex_points[6][1],vertex_points[7][2],vertex_points[6][2]}};
            int counter = 0; 
            
            for(int i=0;i<12;i++){
                int x1 = edges_matrix[i][0];
                int y1 = edges_matrix[i][1];
                int x2 = edges_matrix[i][2];
                int y2 = edges_matrix[i][3];
                int z1 = edges_matrix[i][4];
                int z2 = edges_matrix[i][5];
            if(x1 == x2 && z1==z2){
                        int lower_bound = min(y1,y2);
                        int upper_bound = max(y1,y2);
                        for(int d=lower_bound;d<=upper_bound;d++){
                            int y = d;
                            int x = x1; 
                            int z = z1;    
                            cube_points[counter][0] = x;
                            cube_points[counter][1] = y;
                            cube_points[counter][2] = z;
                            cube_points[counter][3] = i;
                            counter++;
                        }
                    }else if(y1 == y2 && z1==z2){
                        int lower_bound = min(x1,x2);
                        int upper_bound = max(x1,x2);
                        for(int d=lower_bound;d<=upper_bound;d++){
                            int y = y1;
                            int x = d;
                            int z = z1;         
                            cube_points[counter][0] = x;
                            cube_points[counter][1] = y;
                            cube_points[counter][2] = z;
                            cube_points[counter][3] = i;
                            counter++;
                        }
                    }else{
                        int lower_bound = min(z1,z2);
                        int upper_bound = max(z1,z2);
                        for(int d=lower_bound;d<=upper_bound;d++){
                            int y = y1;
                            int x = x1;
                            int z = d;         
                            cube_points[counter][0] = x;
                            cube_points[counter][1] = y;
                            cube_points[counter][2] = z;
                            cube_points[counter][3] = i;
                            counter++;
                        }
                    }
            
            }
        }

        void load_cube(){
            //load matrix with blank spaces
            for(int i = 0; i<n; i++){
                for(int j = 0; j<n; j++){

                    *(*(array+i)+j) = ' ';
                }
            }

            for(int i=0;i<300;i++){

                int x = centar + cube_points[i][0]; 
                int y = centar + cube_points[i][1];
                *(*(array+y)+x) = '.';
                
            }

            //CUBE VERTIXES
            for(int i = 0; i<8;i++){ 
                //x and y coordinates in array space
                int x = centar + vertex_points[i][0]; 
                int y = centar + vertex_points[i][1]; 
                *(*(array+y)+x) = '#';                
            }

        }

};

int main(){

 for(int x = 0; x<=360;x++){
    Qube Q;
    Q.Rotate(x,x,x);
    Q.Print();
    this_thread::sleep_for(chrono::milliseconds(50));
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}


return 0;
}