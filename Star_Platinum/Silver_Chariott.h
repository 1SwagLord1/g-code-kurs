//
// Created by Алексей Михайлов on 12/12/2018.
//

#ifndef STAR_PLATINUM_SILVER_CHARIOTT_H
#define STAR_PLATINUM_SILVER_CHARIOTT_H

#endif //STAR_PLATINUM_SILVER_CHARIOTT_H

///interpretator

#include <stdio.h>
#include <stdlib.h>
void inter() {
    char buff=0, buffs[40], fin[13], M[3];
    for (int cr=0;cr<23;cr++)
    {
        fin[cr]=' ';
    };
    M[0]='M';
    fin[0]='P';
    fin[1]='X';
    fin[2]='A';
    fin[6]='P';
    fin[7]='Y';
    fin[8]='A';


    FILE *Fin, *Fout;
    Fin=fopen("Gcod_in.txt","a");
    Fout=fopen("Gcod_out.txt","w");
    if ((!Fin==NULL)&&(!Fout==NULL)){
        printf("open\n");
        double x=0,y=0,m=0;
        int is=0, kl;
        int imax, kek=0,Q=0;
        while((buff=fgetc(Fin))!=EOF){
            if (kek==4)
            {kek=0;}
            if (buff=='Y'){
                for(int i=0;buff=fgetc(Fin);i++){
                    buffs[i]=buff;
                    if ((buff!=' ')&&(buff!='\n'))
                        fin[9+i]=buff;
                    if ((buff==' ')||(buff=='\n')){

                        buffs[i+1]=EOF;
                        break;
                    }
                    if (i>imax)imax=i;
                }
                switch (imax){
                    case 0:
                        fin[11]=fin[9];
                        fin[9]='0';
                        fin[10]='0';
                        break;
                    case 1:
                        fin[11]=fin[10];
                        fin[10]=fin[9];
                        fin[9]='0';
                        break;
                }
                imax=0;
                kek++;
            }
            ////////////////////////////////////////
            if (buff=='X'){
                for(int i=0;buff=fgetc(Fin);i++){
                    buffs[i]=buff;
                    if ((buff!=' ')&&(buff!='\n'))
                        fin[3+i]=buff;
                    if ((buff==' ')||(buff=='\n')){
                        buffs[i+1]=EOF;
                        break;
                    }
                    if (i>imax)imax=i;
                }
                switch (imax){
                    case 0:
                        fin[5]=fin[3];
                        fin[3]='0';
                        fin[4]='0';
                        break;
                    case 1:
                        fin[5]=fin[4];
                        fin[4]=fin[3];
                        fin[3]='0';
                        break;
                }
                imax=0;
                kek++;

            }

            ///////////////////////////////////////

            ///////////////////////////////////////
//            if (buff=='G'){
//                for(int i=0;buff=fgetc(Fin);i++){
//                    buffs[i]=buff;
//                    if ((buff!=' ')&&(buff!='\n')){
//                        fin[18]=buff;}
//                    if ((buff==' ')||(buff=='\n')){
//
//                        buffs[i+1]=EOF;
//                        break;
//                    }
//                }
//                kek++;
//
//            }
//            ///////////////////////////////////////////

            if (buff=='M'){
                for(int i=0;buff=fgetc(Fin);i++){
                    buffs[i]=buff;
                    if ((buff!=' ')&&(buff!='\n'))
                        M[1+i]=buff;
                    if ((buff==' ')||(buff=='\n')){

                        buffs[i+1]=EOF;
                        break;
                    }
                }
                Q++;
            }

            if (Q==1) {for (int o=0;o<3;o++){
                    printf("%c",M[o]);
                    if (o==2) printf("\n");
                }
                fwrite(M, 3, 1, Fout);
                fputc('\n',Fout);
                Q=0;
            }

            if (kek==2) {for (int o=0;o<13;o++){
                    printf("%c",fin[o]);
                    if (o==12) printf("\n");
                }
                fwrite(fin, 13, 1, Fout);
                fputc('\n',Fout);
                kek=0;
            }


        }
    }
    else{
        printf("ne open\n");
    }
    fclose(Fin);
    fclose(Fout);
    //system ("pause");
};