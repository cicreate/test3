#include <iostream>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <cstdio>
using namespace std;
int foodn=2/*anvae food*/,drinkn=2/*anvae drink*/, n/*tedad moshtarie hazer*/, cap=6;/*jame zarfiathaie food*/
int breadready=0/*tedad breade amade*/, bonus=0/*sud*/, money=0 /*pule kol*/, breadcap=4 /*zarfiate nan*/;
int  breadprice=2/*gheimate nan*/, breadinproc=0, /*tedade breade dar hale amade shodan*/ breadctime=1;/*zamane amade shodan*/
char ss[100]; /*baraie zakhire saziha*/
class drink {
public:
char name[100];
int cap,ctime,ready=0;/*cap=zarfiat, ctime=zamane amade shodan, ready=tedad drink e amade*/
int price, inproc=0; /*inproc=inprocess tedade dar hale amade shodanha*/
}d[100];

class food{
public:
char name[100];
int cap, type,ctime,cookedn=0,cookingn=0,price; /*type=0|1 without|with bread, cookingn=tedad foode dar hale pokht, cookedn=tedad foode pokhte*/
}f[100];
class costumer{
public:
char ID[3];
int presence=0/*0|1 ghaieb|hazer*/, patience=0/*tahamol*/, time=0/*zamane gozashte az vorud*/;
int foodord[100]={0} /* food order 0|1|2 sefaresh nadade|dade hanuz nagerefte|dade gerefte */,drinkord[100]={0};/*drink order (mesle food)*/
int Unrecieved=0, Recieved=0;//tedad sefareshe dariaf shode (Recieved), tedad sefareshe dariaft nashode (Unrecieved)
}a[7];

class cook {
public:
int time=-1, foodcode; //time: ghabl az por shodan ba dastur -1 ast, agar dasture pokht mojaz bud time 0 va harbar dar next +10 mishavad
}c[1000];
void custom() {
    int a, b;
    char s[100];
    cout << "How many foods do you want to add?";
    cin>>a;
    foodn=a+2;
    for(int i=2; i<a+2; i++) {
        cout<<endl<<"Food name:";
        cin>>f[i].name;
        cout << endl << "0.without bread  1.with bread";
        cin >> f[i].type;
        cout<< endl << "Capaticy:";
        cin >> f[i].cap;
        cap +=f[i].cap; //agar error nemidad mishod c[cap] ra tarif kard
        cout << endl << "Price:";
        cin >> f[i].price;
        cout<<endl<<"Cooking time:";
        cin>>f[i].ctime;
    }
        cout << "Do you want to change default foods? (0=No, 1=Yes)";
        cin >> b;
        if (b==1){
            cout<<endl<<"chicken sandwich: (0=defaualt, 1=change)";
            cin >> b;
            if (b) {
                    cout << endl << "0.without bread  1.with bread";
                    cin >> f[0].type;
                    cout<< endl << "Capaticy:";
                    cin >> f[0].cap;
                    cap+=f[0].cap;
                    cout << endl << "Price:";
                    cin >> f[0].price;
                    cout<<endl<<"Cooking time:";
                    cin>>f[0].ctime;
                    }
            cout<<endl<<"meat sandwich: (0=defaualt, 1=change)";
            cin >> b;
            if (b==1) {
                    cout << endl << "0.without bread  1.with bread";
                    cin >> f[1].type;
                    cout<< endl << "Capaticy:";
                    cin >> f[1].cap;
                    cap+=f[1].cap;
                    cout << endl << "Price:";
                    cin >> f[1].price;
                    cout<<endl<<"Cooking time:";
                    cin>>f[1].ctime;
                    }
            }
cout<<endl;

}

void putgive(int foodcode, int giver) { //foodcode=shomareie food dar f[100], giver=shomareie girande dar a[7]
    if (f[foodcode].type==0) {cout<<"It's not served with bread"<<endl;} //check mikone ba nan serve beshe
    else {
         if(a[giver].foodord[foodcode]==1) { //agar giver sefaresh dade va tahvil nagerefte:
            if (f[foodcode].cookedn==0 || breadready==0) { //agar tedad bread ia food 0 bashe mige hazer nist
                cout<<"There isn't ready bread or "<<f[foodcode].name<<endl;}
            else {
                breadready--; //tedad bread kam
                f[foodcode].cookedn--; //foode pokhte kam
                a[giver].foodord[foodcode]=2; //2=sefaresh dade va gerefte
                a[giver].Recieved++;//tedad dariafti ieki ziad
                a[giver].Unrecieved--;//tedad dariaft nashode ieki kam
                }
           }
         else cout<<"haji dari eshtebah mizani!"<<endl; //agar a[i].f[j] = 0 | 2 bashad dastur ghalat ast (sefaresh nadade ia ghablan gerefte)
    }
}
void give(int foodcode, int giver, int givetype) { //givetype= 0|1 : drink|food
    if (givetype==1) { //agar food bashe
        if (f[foodcode].type==1) {cout<<"It's served with bread"<<endl;} //check mikone ba nan serve nashe
        else {
            if(a[giver].foodord[foodcode]==1) { //check mikone giver sefaresh dade va nagerefte bashe
                if (f[foodcode].cookedn==0) { //tedad ghazaie pokhte 0 nabashe
                cout<<"There isn't ready "<<f[foodcode].name<<endl;}
                else {
                f[foodcode].cookedn--;
                a[giver].foodord[foodcode]=2;//2=sefaresh dade va gerefte
                a[giver].Recieved++;//tedad dariafti ieki ziad
                a[giver].Unrecieved--;//tedad dariaft nashode ieki kam
                }
            }
            else cout<<"haji dari eshtebah mizani!"<<endl; //agar a[i].f[j] = 0 | 2 bashad dastur ghalat ast (sefaresh nadade ia ghablan gerefte)
        }
   }
   else {//agar drink bashe
    if (a[giver].drinkord[foodcode]==1) { //marahele moshaabehe food baraie drink
            if (d[foodcode].ready==0)
            {cout<<"There isn't ready "<<d[foodcode].name<<endl;}
            else {
                d[foodcode].ready--;
                a[giver].drinkord[foodcode]=2;
                a[giver].Recieved++;
                a[giver].Unrecieved--;
                }
        }
    else cout<<"haji dari eshtebah mizani!"<<endl;;
   }

}
void cook (int i){ //dasture pokht, i= shomare dastur
    int k= c[i].foodcode; //shomareie food dasture i ra dar k zakhire
    if (c[i].time >= f[k].ctime) { //agar zamane pokht be zamane morede niaze food resid
        f[k].cookedn++; //tedad pokhteie food ieki ziad
        f[k].cookingn--; //tedad napokhteie food ieki kam
        c[i].time=-1; //dasture pokht digar motevaghef mishavad ba -1 shodane zamanash
    }
    else if (c[i].time == -1) { //vaghti pokht shoru nashode
        if( (f[k].cookedn + f[k].cookingn) == f[k].cap) { //check mikonad zarfiat dashte bashad (darhale pokht + pokhte <=zarfiat)
            cout<<"There isn't enough space for that"<<endl;
        }
        else if (f[k].ctime == 0) f[k].cookedn++; //agar zamane morede niaze food 0 bashad, dar lahze hazer ast
        else { //ja darad va zamane food 0 nist, pas darhale pokht ra ieki ezafe va zaman ra 0 mikonad (start)
            f[k].cookingn++;
            c[i].time=0;
        }
    }
}
void randcostumer(){ //tolide moshtarie jadid
    srand(time(NULL));
    int t=0; //tedad ghaieb ha
    int m = rand()%(8-n); //tedad moshtarie jadid, 0 ta 7-n
    n +=m;
    for (int i=0; i<7; i++){
        if (a[i].presence==0) { //ghaieb ha zaman va tedad sefaresh az har noeshan 0 mishavad
            t++;
            a[i].time =0;
            a[i].Recieved=0;
            a[i].Unrecieved=0;
            if(t<= m){ //ta vaghti tedad ghaieb ha be m beresad (chon m ghaieb ra mikhahim hazer konim)
              a[i].presence=1; //hazer shodan
              a[i].patience=rand()%31+20; //tahamole random 20 ta 50
              for (int j=0; j<foodn; j++) {
                a[i].foodord[j]=rand()%2; //har food random 0/1 (dade ia nadade)
                if (a[i].foodord[j]) {a[i].Unrecieved++;}} //foodord[j]=1 pas sefresh dade va unrecieved ra ziad
              for(int j=0; j<drinkn; j++){ //har drink random 0/1
                a[i].drinkord[j]=rand()%2;
                if(a[i].drinkord[j]) a[i].Unrecieved++;}
              if (a[i].Unrecieved==0) { //agar 0 sefaresh dade bashad, ieki ra random 1 mikonad
                m=rand()%foodn; //random beine 0 - (foodn-1)
                a[i].foodord[m]=1; //foode m om ra sefaresh dade mikonad!
                a[i].Unrecieved=1;} //tedad sefaresh 1
            }
        }

    }
}
void showcostumer(){ //namaieshe moshtariha ba moshakhasat
for (int i=0; i<7; i++){
    if (a[i].presence==1){ //hazerin
        cout<<endl<< 1+i <<"  "<<a[i].patience - a[i].time << "s  "; //ID va zamane mande az sabr
        for (int j=0; j<foodn; j++){
            if (a[i].foodord[j]){ //food != 0 iani sefaresh dade
                cout<<f[j].name;//esme food
                if (a[i].foodord[j]==2) cout<<"(R)  "; //food dariaft shode
                else cout<<"(UR)  ";//food dariaft nashode
            }
        }
        for(int j=0; j<drinkn; j++){ //moshabehe food baraie drink
            if(a[i].drinkord[j]){
                cout<<d[j].name;
                if(a[i].drinkord[j]==2) cout<<"(R)  ";
                else cout<<"(UR)  ";
            }
        }
    }
}
cout<<endl;
}
void calculate(int costumer){ //hesabe pule moshtarie mojaze dar hale khoruj
    for(int j=0; j<foodn; j++)
       {if (a[costumer].foodord[j]==2){money += f[j].price;} //pule kol ra ba gheimate food jam mizanad
        if(f[j].type==1){money += breadprice;} //agar ba bread bud, gheimate bread ra ham jam mizanad
       }
    for(int j=0; j<drinkn; j++) if (a[costumer].drinkord[j]==2){ money += d[j].price;}//hamchenin drink
}
void check(){ //namaieshe aghlam
cout<<"**bread"<<":{"<<endl<<"  ready:"<<breadready<<endl<<"  in process:"<<breadinproc<<"}"<<endl<<endl;
for (int i=0; i<foodn; i++){
    cout<<"**"<<f[i].name<<":{"<<endl<<"  cooked:"<<f[i].cookedn<<endl<<"  cooking:"<<f[i].cookingn<<"}"<<endl<<endl;}
for (int i=0; i<drinkn; i++){
    cout<<"**"<<d[i].name<<":{"<<endl<<"  ready:"<< d[i].ready<<endl<<"  in process:"<<d[i].inproc<<"}"<<endl<<endl;}
}
void next() {
int bonus=0, temp=0;
//hesabe anaam: (mitavan in ghesmat ra dar main ham gozasht)
for (int i=0; i<7; i++){
    if(a[i].presence==1 && a[i].Unrecieved==0 && a[i].time==0) //agar moshtari hazer, zaman va sefareshe dariaft nashode ash 0
        {bonus += 2; //2 bit jam ba anaame kol
        a[i].presence=0; //khoruje moshtari
        calculate(i);//hesabe pulash
        }
    }
//hesabe pul va zarar ba tavajoh be khoruj, jolo bordane a[i].time e hame:
for (int i=0; i<7; i++){
    if (a[i].presence==1) {
       a[i].time +=10; // zamane hazerin jolo miravad
       if(a[i].time >= a[i].patience){ //agar zamane gozashte bishtarmosavie tahamol:
         a[i].presence=0; //khoruj a[i]
         n--; //tedad hazerin kam
         if(a[i].Unrecieved > 0) { bonus -= 2 * a[i].Recieved;} //agar unrecieved dasht zarar agar na pul ra hesab
         else calculate(i);
       }
       else if (a[i].Unrecieved==0){ //zudtar az tahamol sefaresh ra gerefte
            calculate(i);
            a[i].presence=0;
            n--;
       }
    }
}
//jolo bardane zamane dastur haie pokht:
for(int i=0; i<1000; i++) {
if(c[i].time != -1) {c[i].time+=10; cook(i);} //agar dastur -1 nabud(dade shode iani), zamanash ra +10
}
money += bonus;
randcostumer(); //moshtarihaie jadid
showcostumer(); //namaieshe moshtariha
//amade kardane drink ha:
for (int i=0; i<drinkn; i++) {
    if(d[i].ready + d[i].inproc < d[i].cap) { //ba har next, agar hanuz zarfiat por nashode
        d[i].inproc ++;//iek drink ra dar hale amade shodan migozarad
    }
    d[i].ready = d[i].inproc / (d[i].ctime/10 + (d[i].ctime % 10)*1 ); /* tedad game morede niaz baraie amade shodane iek drink*/
  } //ba taghsime dar hale amade ha bar tedad gam, tedad ready ha be dast miaiad (joze sahih)
//amade kardane bread:
breadinproc++;
breadready= breadinproc / (breadctime/10 + (breadctime%10)*1);

cout<<endl<<"Money: "<< money<<endl;
}


main() {
//default game information:
strcpy(d[0].name, "yogurt");
strcpy(d[1].name, "soda");
d[0].cap= 3; d[1].cap=3;
d[0].ctime=10; d[1].ctime=10;
d[0].ready=0; d[1].ready=0;
d[0].price=2; d[1].price=3;
strcpy(f[0].name,"chicken"), strcpy(f[1].name,"meat");
f[0].type=1, f[0].cap=3, f[0].price=8, f[0].cookedn=0, f[0].cookingn=0, f[0].ctime=20;
f[1].type=1, f[1].cap=3, f[1].price=12, f[1].cookedn=0, f[1].cookingn=0, f[1].ctime=30;

//sakhte moshtari haie avalie: (moshabehe tabeie rancostumer)
strcpy(a[0].ID,"1");
strcpy(a[1].ID,"2");
strcpy(a[2].ID,"3");
strcpy(a[3].ID,"4");
strcpy(a[4].ID,"5");
strcpy(a[5].ID,"6");
strcpy(a[6].ID,"7");

srand(time(NULL));
n = rand()%7 +1;
int m;
for (int i=0; i<7; i++){
        if (i<n){
            a[i].Unrecieved=0;
            a[i].Recieved=0;
            a[i].time=0;
            a[i].presence=1;
            a[i].patience=rand()%31+20;
            for (int j=0; j< foodn; j++) {
                a[i].foodord[j]=rand()%2;
                if (a[i].foodord[j]==1) a[i].Unrecieved +=1;}
            for(int j=0; j<drinkn; j++){
                a[i].drinkord[j]=rand()%2;
                if(a[i].drinkord[j]==1) a[j].Unrecieved +=1;}
            if(a[i].Unrecieved==0){
            m = rand()%foodn;
            a[i].foodord[m]=1;
            a[i].Unrecieved=1;}
        }
}


int x, k;
char st[500], tool[500], s[100];
cout<<"1.New Game   2.Customize"<<endl;
cin>>x;
if (x==2) {
custom();
}
else if(x != 1) {cout<<"Typing Error!";}

showcostumer(); //namaieshe customer haie avalie
cout<<endl;
gets(ss);

while(1) {


             gets(st);
             int error, foodcode=-1, giver=-1, givetype; //givetype= 0|1 : drink|food
             error=1; //for typing error
             tool[500]=NULL;
             if(strstr(st,"cook")){

                for(int i=0; i<foodn;i++){
                    strcpy(tool,"cook ");
                    strcat(tool, f[i].name);
                    if (strcmp(st,tool)==0){error=0; foodcode=i;} //foodi ke type shode ro peida, foodcode=shomarie food
                }//jomleie type shode ro ba cook + foodname tatabogh
                if(error==1) {cout<<"Typing Error!"<<tool<<endl;}
                else { //agar error nadasht
                    for (int i=0; i<1000; i++)
                    if (c[i].time == -1) { c[i].foodcode=foodcode; cook(i); break;} //avalin c[i] khali peida va mifreste be tabeie cook
                }

             }
             else if (strstr(st,"give")) {
                if(strstr(st,"put")){

                    for(int i=0; i<foodn; i++){
                        if(strstr(st,f[i].name)) {error=0; foodcode=i;}}
                    if(error) cout<<"Typing Error(foodname)!"<<endl; //tatbighe foodname
                    for (int i=0; i<n; i++){ //peida kardane ID va sakhtane jomle dar tool[]
                            if(strstr(st, a[i].ID)){
                                giver=i;
                                strcpy(tool,"put ");
                                strcat(tool, f[foodcode].name);
                                strcat(tool, " into bread and give to ");
                                strcat(tool, a[i].ID);
                                break;
                                }
                        }

                        if (giver==-1){cout<<"Typing Error(Giver name)!"<<endl;} //vojude ID e motabar
                        else if (strcmp(st, tool)) {cout<<"Typing Error(Extra words)!"<<endl;}//tatbighe jomle
                        else if (error==0) { putgive(foodcode, giver);} //agar error nadasht tabeie putgive seda

                  }
                else {

                        for(int i=0; i<foodn; i++){
                           if(strstr(st,f[i].name)){error=0; foodcode=i; givetype=1;}} //givetype=1 food
                        for (int i=0; i<drinkn; i++){
                            if(strstr(st,d[i].name)){error=0; foodcode=i; givetype=0;}}//givetype=0 drink
                        if(error) cout<<"Typing Error(foodname)!"<<endl; //tatbighe foodname/drinkname
                        //peida kardane ID va sakhtane jomle dar tool[]
                        for (int i=0; i<n; i++){
                            if(strstr(st, a[i].ID)){
                                giver=i;
                                strcpy(tool,"give ");
                                if(givetype==1) strcat(tool, f[foodcode].name);
                                else strcat(tool, d[foodcode].name);

                                strcat(tool," to ");
                                strcat(tool,a[i].ID);
                                break;
                                }
                        }

                        if (giver==-1){cout<<"Typing Error(Giver name)!"<<endl;} //vojude ID e motabar
                        else if (strcmp(st, tool)) {cout<<"Typing Error(Extra words)!"<<endl;}//tatbighe jomle
                        else if (error==0) {give(foodcode, giver, givetype);}//agar error nadasht tabeie give seda
                    }

                }

            else if (strstr(st,"next")) {
                    if (strcmp(st,"next")) {cout<<"Typing Error (Extra words)!"<<endl;}
                    else {next();}
            }
            else if (strstr(st,"check")) {
                    if (strcmp(st,"check")) {cout<<"Typing Error (Extra words)!"<<endl;}
                    else {check();}
            }
            else {cout<<"Typing Error (Extra words)e!"<<endl;}

        }
}


