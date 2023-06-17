// #include <iostream>
// using namespace std;

/*====== to do list: ======*/
// change cmd from "fbrlse" to "nwsemc"
// determine how checkcmd function send error message
// (halt malissa and request correct map?)
// (dream)output malissa's position to users
/*====== jia yooooo! ======*/


enum dir_{//direction
    DIR_N, DIR_W, DIR_S, DIR_E, DIR_ENDP
};

dir_ operator+(dir_ a, dir_ b){
    int a_int = a; int b_int = b;
    dir_ ret;
    switch ((a_int+b_int)%4){
        case 0: ret = DIR_N; break;
        case 1: ret = DIR_W; break;
        case 2: ret = DIR_S; break;
        case 3: ret = DIR_E; break;
    }
    return ret;
}

dir_ operator-(dir_ a, dir_ b){
    int a_int = a; int b_int = b;
    dir_ ret;
    switch ((4+a_int-b_int)%4){
        case 0: ret = DIR_N; break;
        case 1: ret = DIR_W; break;
        case 2: ret = DIR_S; break;
        case 3: ret = DIR_E; break;
    }
    return ret;
}

enum env_{//environment parameter
    ENV_T, ENV_L, ALLENV
};

class Block
{
  private:
  int pot=10;
  int env[ALLENV]={};
  dir_ cmd[2]={DIR_N, DIR_N};

  public:
  //constructor: store and convert cmds
  ~Block(){}
  Block(){}
  Block(char t, char b){
    switch (t){
        case 'f': cmd[0] = DIR_N; break;
        case 'l': cmd[0] = DIR_W; break;
        case 'b': cmd[0] = DIR_S; break;
        case 'r': cmd[0] = DIR_E; break;
        case 'e': cmd[0] = DIR_ENDP; break;
    }
    switch (b){
        case 'f': cmd[1] = DIR_N; break;
        case 'l': cmd[1] = DIR_W; break;
        case 'b': cmd[1] = DIR_S; break;
        case 'r': cmd[1] = DIR_E; break;
        case 's': cmd[1] = DIR_ENDP; break;
    }
  }

  //environment algorithm: 
    void update_env(int []);

  friend class Map;

};

void Block::update_env(int rawenv[ALLENV]){
    //need an algorithm
    for(int i=0; i<ALLENV; i++)env[i] = rawenv[i];
}



class Map
{
    private:
    int M, N, lenx, leny;
    int x, y, r=0, c=0;
    dir_ dir = DIR_E;
    Block **blocks = NULL;
    
    bool notfetchcmd = true;
    bool tb = false;
    //for setting up a map
    int index = 1;
    bool getparam(char s[], char *param);
    bool getparam(char s[], int *param);
    bool checkcmd();

    public:
    //setup a map
    Map(char *);
    ~Map(){
        for(int i=0; i<M; i++)delete [] blocks[i];
        delete [] blocks;
    }

    //check in loop
    void update(int, int, int []);

    //just for testing
    void printmap();

};

bool Map::checkcmd(){
    int check_x = 0, check_y = 0;
    bool check_tb = false;
    dir_ check_cmd;
    dir_ check_dir = DIR_E;
    // cout << "checking cmd..."<<endl;
    for(int i=0; i<M*N*2; i++){
        if(blocks[check_x][check_y].cmd[check_tb] == DIR_ENDP){
            check_cmd = (DIR_N-check_dir); check_tb =1-check_tb;}
        else check_cmd = (blocks[check_x][check_y].cmd[check_tb]+check_dir);
        check_y += ((int)check_cmd%2)*((int)check_cmd-2);
        check_x += (((int)check_cmd+1)%2)*((int)check_cmd-1);
        check_dir = check_cmd;
        cout <<"dir="<<check_dir;
        cout <<" (x, y)=("<<check_x<<", "<<check_y<<")"<<endl;
        if(check_x<0||check_x>=M||check_y<0||check_y>=N){/*cout << "cmd is wrong"<<endl*/;return false;}
        if(check_x==0&&check_y==0){/*cout << "cmd is correct!"<<endl;*/ return true; }
    }
    return false;
}

/*
void Map::printmap(){
    //static int test_HCSR04[4] = {9, 0, 0, 8};
    static int test_env[ALLENV] = {45, 46};
    static int test_x = 0;
    static int test_y = 0;
    if((int)dir%2==0)test_y+=dir-1;
    else test_x+=dir-2;
    // test_HCSR04[DIR_N-dir] = test_y;
    // test_HCSR04[DIR_W-dir] = test_x;
    // test_HCSR04[DIR_S-dir] = M*leny-test_y;
    // test_HCSR04[DIR_E-dir] = N*lenx-test_x;
    // cout << "fake HCSR04(N, W, S, E) = ";
    // for(int i=0; i<4; i++)cout << test_HCSR04[i] << " ";
    cout << endl;
    update(test_x, test_y, test_env);

    cout << "(x, y)=(" << x << ", "<<y;
    cout << "), (r, c)=("<< r <<", "<<c;
    cout << "), dir = "<<(int)dir <<endl;
    for(int i=0; i<M*leny; i++){
        if(i%leny == 0){
            for(int j=0; j<N*lenx; j++){
                if(j%lenx == 0)cout << "+ ";
                cout << "- ";
            }
            cout << "+"<<endl;
        }

        for(int j=0; j<=N*lenx; j++){
            if(j%lenx == 0 )cout << "| ";
            if(i==y && j==x){
                if(dir == DIR_N) cout << "^ ";
                else if (dir == DIR_W) cout << "< ";
                else if (dir == DIR_E) cout << "> "; 
                else cout << "v "; 
            }
            else cout << "  ";
        }
        cout << endl;
    }
    for(int j=0; j<N*lenx; j++){if(j%lenx == 0)cout << "+ "; cout << "- ";}
    cout << "+"<<endl;
}

*/
void Map::update(int getx, int gety, int rawenv[ALLENV]){

    // read x, y from HCSR04
    /*
    if(HCSR04[DIR_W-dir]<HCSR04[DIR_E-dir])x = HCSR04[DIR_W-dir];
    else x = N*lenx - HCSR04[DIR_E-dir];
    if(HCSR04[DIR_N-dir]<HCSR04[DIR_S-dir])y = HCSR04[DIR_N-dir];
    else y = M*leny - HCSR04[DIR_S-dir];*/
    x = getx; y = gety;

    // change its position
    // highly depend on the correctness of the sensor; 
    // may need algorithm to eliminate abrupt bug of the data
    if(r != y/leny){r = y/leny; notfetchcmd = true;}
    if(c != x/lenx){c = x/lenx; notfetchcmd = true;}

    //read environment parameter
    blocks[r][c].update_env(rawenv);
    
    //decide whether to move on to the next block
    if(notfetchcmd){
        switch(dir){
            case DIR_N:
            if(y%leny <= leny/2)goto fetchcmd; else break;
            case DIR_S:
            if(y%leny >= leny/2)goto fetchcmd; else break;
            case DIR_E:
            if(x%lenx >= lenx/2)goto fetchcmd; else break;
            case DIR_W:
            if(x%lenx <= lenx/2)goto fetchcmd; else break;
            fetchcmd:
            if(blocks[r][c].cmd[tb]==DIR_ENDP){
                //cout << "!!!!!!!!!!! reverse !!!!!!!!!!!" << endl;
                //Call the motor to reverse its direction
                dir = dir + DIR_S; notfetchcmd = false;
                tb = 1-tb;
            }else{
                //cout << "!!!!!!!!!!! fetch cmd: " <<blocks[r][c].cmd[tb]<<" !!!!!!!!!!!"<<endl;
                //Call the motor to execute the cmd
                dir = dir + blocks[r][c].cmd[tb];
                notfetchcmd = false;
            }
            default: break;
        }
    
    }


    


    /*adjust the direction, lateral position and velocity*/
    //direction
    
    //lateral position

    //velocity
    
    

    
}



/*========== Map constructor ===========*/
// create a map and store commands in
Map::Map(char *s){
    index = 1;
    // get the scales of the map and block
    getparam(s, &M);
    getparam(s, &N);
    getparam(s, &lenx);
    getparam(s, &leny);

    //get the commands of each block
    char *to_temp, *back_temp;
    to_temp = new char[M*N+1];
    back_temp = new char[M*N+1];
    getparam(s, to_temp);
    getparam(s, back_temp);

    //create a map of blocks and store the commands
    blocks = new Block *[M];
    for(int i=0; i<M; i++){
        blocks[i] = new Block[N];
        for(int j=0; j<N; j++){
            blocks[i][j] = Block(to_temp[i*N+j], back_temp[i*N+j]);
            index++;
        }
        
    }
    if(!checkcmd());
    delete [] to_temp;
    delete [] back_temp;
}

//parameter processor for scales
bool Map::getparam(char s[], int *param){
    *param = 0;
    char param_name[10];
    for(int i=0; s[index]!=':' && index < 1000 && s[index]!='\0'; i++){
        if(s[index]!=' ')param_name[i]=s[index];
        index++;
    }
    index++;
    while(s[index]!=',' && index < 1000){
        *param *= 10;
        *param += s[index]-'0';
        index++;
    }
    index++;
    return true;
}

//parameter processor for commands
bool Map::getparam(char s[], char *param){
    // read the title
    char param_name[10];
    for(int i=0; s[index]!=':' && index < 1000 && s[index]!='\0'; i++){
        if(s[index]!=' ')param_name[i]=s[index];
        index++;
    }
    index++;//read ':'

    // read the commands
    for(int i=0; s[index]!=',' && s[index]!='}' && index < 1000; i++){
        if(i<M*N)param[i]=s[index];
        
        cout << param[i] << endl;
        if(param[i]!='f'&&param[i]!='l'&&param[i]!='r'&&param[i]!='b'&&param[i]!='s'&&param[i]!='e')return true;
        index++;
    }
    param[M*N] = '\0';


    index++;
    return false;

}




/*


void testfunct(){
    Block **b = NULL;
    b = new Block *[2];
    b[0] = new Block[2];
    cout << "hi!" << endl;
}


int main(){
    //testfunct();
    char s[] = "{M:2, N:3, lenx:4, leny:3, actiont:ffrefr, actionu:sflffl}";
    Map map(s);
    char c = '\0';
    cin >> c;
    while(c=='n'){
        map.printmap();
        cin >> c;
    }
    
}

*/