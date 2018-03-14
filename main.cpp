#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include "DVM_fichier.h"

using namespace std;

class Client{
     public : std::string nom, prenom, contact,mdp;
     int numCompte;

     int attributNumCompt(int inf,int sup)
     {
         int alea;
         srand(time(NULL));
         alea=rand();
         alea=(alea%(sup-inf))+inf;
         cout <<"alea "<<alea;
         return alea;
     }
};

class Compt{
public :    int numCompt;
    int solde;
    public : std::string dateCreation;
};

/**
* Les fonctionpour gerer les comptes*/

bool CreClient(Client clien, std::string cheminFichier);

bool CreCompt(Compt compte, std::string fichierCompte);

bool CreTransaction(int numCompt, std::string dates, std::string tipe, int montant, std::string fichierTrans);

bool SuprimClient(int numCompt,string fichierClient);
bool SuprimCompt(int numCompt,string fichierCompt);
bool SuprimTrans(int numCompt,string fichierTrans);

Client RecuperClient(int numCompt, string fichierClient);

Compt RecuperCompt(int numCompt, string fichierCompt);

std::string RecuperTrans(int numCompt,std::string fichierTrans);


/**
* Les fonction pour concatenner des string en int*/
int cInt(string ch);
int nDizaine(int n);
bool isNumeric(string ch);



string const cheminFichierClient("Clients.txt");
string const cheminFichierCompt("Bilan.txt");
string const cheminFichierTransaction("Transaction.txt");

int main()
{
    Client clien;
    Client clientPris;
    Compt compte;
    string transaction;
    int const a(13569),b(99999);

    int choix,quit(1);
    do{
        system("CLS");
         cout <<"-------*******Bienvenue a votre banque*******-------\n";
         cout <<"1-Creer compte\n2-Connexion au Compte\n3-Quitter\n";
         cin >>choix;
         cin.ignore();

        if(choix==1)
        {
            cout <<"-----Creation de compte-----\n";
            //les info du client
            cout <<"Vos informations:\nNom :";
            getline(cin, clien.nom);

            cout <<"Prenoms : ";
            getline(cin,clien.prenom);

            cout <<"Contacts : ";
            getline(cin,clien.contact);

            cout <<"Mot de passe : ";
            getline(cin,clien.mdp);

            clien.numCompte=clien.attributNumCompt(a,b);
            cout <<"\n\n";

            //les Infos du compte
            cout <<"-----Compte-----\n";

            compte.numCompt=clien.numCompte; //attribution du numéro de compte
            cout <<"Le montant initial de votre compte : ";
            cin >> compte.solde;cin.ignore();

            cout <<"Date de creation : ";
            getline(cin,compte.dateCreation);

            if(CreClient(clien,cheminFichierClient) && CreCompt(compte,cheminFichierCompt) &&CreTransaction(compte.numCompt,compte.dateCreation,"Versement",compte.solde,cheminFichierTransaction))
            {
                cout <<"Compte Cree avec succes\nVotre numero de compte est "<< clien.numCompte<<". Concervez le bien pour votre connexion\n";
                cin;
            }
            else {
                    cout <<"Erreur l'hors de la creation de compte";
                    cin;
            }
        }
        else if(choix==2)
        {
            system("CLS");
            string mdp;
            cout <<"-------*******Connexion au compte*******-------\n\n";
            cout <<"Numero de compte : ";
            cin >>clien.numCompte;

            clien=RecuperClient(clien.numCompte,cheminFichierClient);
            if(clien.numCompte==0)
            {
                cout <<"Ce numero de compte n'existe pas.";
                cin;
                break;
            }

            cout <<"Entrez votre mot de passe";
            cin >>mdp;
            if(!(mdp==clien.mdp))
            {
                cout <<"Mot de passe incorrect.";
                cin;
                break;
            }
            system("cls");
            //LE client accede au compte

            int choixInCompt;
            int montant;
            string dates;
            do{
                    system("cls");
            cout <<"-----*****Bienvenue dans votre banque Mr. "<<clien.nom<<" "<<clien.prenom<<" *****-----\n\n";
            compte=RecuperCompt(clien.numCompte,cheminFichierCompt);
            cout <<"Choisissez une action\n1-Versement\n2-Retrait\n3-Voir solde de compte\n4-Voir mes transactions\n5-Deconnexio\n"; //affichage du menu



            cin >>choixInCompt;
            cin.ignore();
            int soldeCompt;
            switch (choixInCompt)
            {
            case 1:
                soldeCompt=compte.solde;
                cout <<"Actuellement vous avez "<<soldeCompt<<" dans votre compte"<<endl;
                cout <<"Saisissez le montant du versement : ";
                cin >>montant;
                cin.ignore();
                soldeCompt+=montant;
                //cout <<"La variable soldeComport "<< soldeCompt;
                compte.solde=soldeCompt;
                cout<<"Votre solde sera de "<<compte.solde<<endl;

                cout <<"Date : ";
                cin >>dates;

                CreTransaction(clien.numCompte,dates,"Versement", montant, cheminFichierTransaction);
                SuprimCompt(compte.numCompt,cheminFichierCompt);
                CreCompt(compte,cheminFichierCompt);
                compte=RecuperCompt(compte.numCompt,cheminFichierCompt);
                cout <<"Le versement a ete effectue avec succes\n";
                cin;
                break;
            case 2:
                soldeCompt=compte.solde;
                cout <<"Actuellement vous avez "<<soldeCompt<<" dans votre compte\n";
                cout <<"Saisissez le montant du retrait : ";
                cin >>montant;

                soldeCompt-=montant;
                compte.solde=soldeCompt;
                cout <<"Votre solde sera de "<<compte.solde<<endl;

                cout <<"Date : ";
                cin >>dates;

                CreTransaction(clien.numCompte,dates,"Retrait", montant, cheminFichierTransaction);
                SuprimCompt(compte.numCompt,cheminFichierCompt);
                CreCompt(compte,cheminFichierCompt);
                cout <<"Retrait effectue avec succes.\n";
                cin;
                break;
            case 3:
                cout <<"Le solde de votre compte est de : "<< compte.solde<<endl;
                cin;
                break;
            case 4:
                cout <<"Voici vos transactions\n";
                transaction=RecuperTrans(compte.numCompt,cheminFichierTransaction);

                cout << transaction;
                cin;
                break;
            default:
                choixInCompt=5;
                cout <<"Sortie de l'application";
                system("pause");
                break;

            }
            }while(choixInCompt!=5);
        }
        else
        {
            quit=0;
        }


    }while(quit==1);

    return 0;
}


bool CreClient(Client clien, std::string cheminFichier)
{
    ofstream fichierClient(cheminFichier.c_str(), ios::app);

    //if(!fichierClient) fichierClient(cheminFichier.c_str());

    if(!fichierClient) return false;
    else
    {
        fichierClient << clien.numCompte <<std::endl;
        fichierClient << clien.mdp <<std::endl;
        fichierClient << clien.nom << std::endl;
        fichierClient << clien.prenom << std::endl;
        fichierClient << clien.contact << std::endl;
        fichierClient << std::endl << std::endl;

        return true;
    }
}

bool SuprimClient(int numCompt,string fichierClient)
{


    ifstream lireFichierClient(fichierClient.c_str());
    string copieClient("CopieClient.txt");
    string ligneLu;
    int nbrLigneAsauter(7);
    int nbrLigneLu(0);
    int i(0);


    ofstream ecrireFichierClient(copieClient.c_str());

    if(!lireFichierClient) return false;
    else{
            if(!ecrireFichierClient) return false;
            else
            {


                while(getline(lireFichierClient,ligneLu))
                {
                    nbrLigneLu++;
                    if(nbrLigneLu%nbrLigneAsauter==1)
                    {
                        if(cInt(ligneLu)==numCompt)
                        {
                            for(i=0 ; i<nbrLigneAsauter ; i++)
                                {
                                    getline(lireFichierClient,ligneLu);
                                    nbrLigneLu++;
                            }
                        }
                    }

                    ecrireFichierClient << ligneLu << endl;
                }
            }


            lireFichierClient.close();
            remove(fichierClient.c_str());
            ecrireFichierClient.close();
            rename(copieClient.c_str(),fichierClient.c_str());

            return true;
    }

}


bool SuprimCompt(int numCompt,string fichierCompt)
{
    ifstream lireFichierCompt(fichierCompt.c_str());
    string copieCompt("CopieCompt.txt");
    ofstream ecrireFichierCompt(copieCompt.c_str());

     string ligneLu;
    int nbrLigneAsauter(5);
    int nbrLigneLu(0);
    int i(0);


            //Supression de compte
            //nbrLigneAsauter=5;
            if(!lireFichierCompt) return false;
    else{
            if(!ecrireFichierCompt) return false;
            else
            {


                while(getline(lireFichierCompt,ligneLu))
                {
                    nbrLigneLu++;
                    if(nbrLigneLu%nbrLigneAsauter==1)
                    {
                        if(cInt(ligneLu)==numCompt)
                        {
                            for(i=0 ; i<nbrLigneAsauter-1 ; i++)
                                {
                                    getline(lireFichierCompt,ligneLu);
                                    nbrLigneLu++;
                            }
                        }
                    }

                    ecrireFichierCompt << ligneLu << endl;
                }
            }


            lireFichierCompt.close();
            remove(fichierCompt.c_str());
            ecrireFichierCompt.close();
            rename(copieCompt.c_str(),fichierCompt.c_str());

            return true;
    }

}


bool SuprimTrans(int numCompt,string fichierTrans)
{
     ifstream lireFichierTrans(fichierTrans.c_str());
     string copieTrans("CopieTrans.txt");
     ofstream ecrireFichierTrans(copieTrans.c_str());

     string ligneLu;
    int nbrLigneAsauter(2);
    int nbrLigneLu(0);
    int i(0);


     //nbrLigneAsauter=2;
            if(!lireFichierTrans) return false;
    else{
            if(!ecrireFichierTrans) return false;
            else
            {


                while(getline(lireFichierTrans,ligneLu))
                {
                    nbrLigneLu++;
                    if(nbrLigneLu%nbrLigneAsauter==1)
                    {
                        if(cInt(ligneLu)==numCompt)
                        {
                            for(i=0 ; i<nbrLigneAsauter ; i++)
                                {
                                    getline(lireFichierTrans,ligneLu);
                                    nbrLigneLu++;
                            }
                        }
                    }

                    ecrireFichierTrans << ligneLu << endl;
                }
            }


            lireFichierTrans.close();
            remove(fichierTrans.c_str());
            ecrireFichierTrans.close();
            rename(copieTrans.c_str(),fichierTrans.c_str());

            return true;
    }
}

Client RecuperClient(int numCompt, string fichierClient)
{
    ifstream lireFichierClient(fichierClient.c_str());
    //ifstream lireFichierCompt(fichierCompt.c_str());
    //ifstream lireFichierTrans(fichierTrans.c_str());

    string copieClient("CopieClient.txt");
    //string copieCompt("CopieCompt.txt");
    //string copieTrans("CopieTrans.txt");
    string ligneLu;
    int const nbrLigneAsauter(7);
    int nbrLigneLu(0);
    int i(0);
    Client clien;

    if(!lireFichierClient) return clien;
    else{
            bool clientTrouve(false);
        while(getline(lireFichierClient,ligneLu))
        {
            nbrLigneLu++;
            if(nbrLigneLu%nbrLigneAsauter==1)
            {
                if(cInt(ligneLu)==numCompt)
                {
                    clientTrouve=true;
                    for(i=0 ; i<nbrLigneAsauter-2 ; i++)
                    {

                        switch(i)
                        {
                        case 0:
                            clien.numCompte=cInt(ligneLu);
                            //cout << "i=" <<i <<", ligneLu= " << ligneLu << "est-ce le num de compte?"<<endl;
                            break;
                        case 1:
                            clien.mdp=ligneLu;
                            //cout << "i=" <<i <<", ligneLu= " << ligneLu << "est-ce le mot de passe?"<<endl;
                            break;
                        case 2:
                            clien.nom=ligneLu;
                            //cout << "i=" <<i <<", ligneLu= " << ligneLu << "est-ce le nom?"<<endl;
                            break;
                        case 3:
                            clien.prenom=ligneLu;
                            //cout << "i=" <<i <<", ligneLu= " << ligneLu << "est-ce le prenom?"<<endl;
                            break;
                        case 4:
                            clien.contact=ligneLu;
                            //cout << "i=" <<i <<", ligneLu= " << ligneLu << "est-ce le contact?"<<endl;
                            break;
                        }
                        getline(lireFichierClient,ligneLu);
                    }
                    lireFichierClient.close();
                }
            }
        }

        if(clientTrouve)return clien;
    else return clien;
    }

}


Compt RecuperCompt(int numCompt, string fichierCompt)
{
    //ifstream lireFichierClient(fichierClient.c_str());
    ifstream lireFichierCompt(fichierCompt.c_str());
    //ifstream lireFichierTrans(fichierTrans.c_str());

    //string copieClient("CopieClient.txt");
    //string copieCompt("CopieCompt.txt");
    //string copieTrans("CopieTrans.txt");
    string ligneLu;
    int const nbrLigneAsauter(5);
    int nbrLigneLu(0);
    int i(0);
    Compt compte;

    if(!lireFichierCompt) return compte;
    else{
            bool compteTrouve(false);
        while(getline(lireFichierCompt,ligneLu))
        {
            nbrLigneLu++;
            if(nbrLigneLu%nbrLigneAsauter==1)
            {
                if(cInt(ligneLu)==numCompt)
                {
                    compteTrouve=true;
                    for(i=0 ; i<nbrLigneAsauter-2 ; i++)
                    {

                        switch(i)
                        {
                        case 0:
                            compte.numCompt=cInt(ligneLu);
                            break;
                        case 1:
                            compte.solde=cInt(ligneLu);
                            break;
                        case 2:
                            compte.dateCreation=ligneLu;
                            break;
                        }
                        getline(lireFichierCompt,ligneLu);
                    }
                    lireFichierCompt.close();
                }
            }
        }

        if(compteTrouve)return compte;
    else return compte;
    }
}


bool CreCompt(Compt compte, std::string fichierCompte)
{
    ofstream fichierCompt(fichierCompte.c_str(), ios::app);

    //if(!fichierClient) fichierClient(cheminFichier.c_str());

    if(!fichierCompt) return false;
    else
    {
        fichierCompt << compte.numCompt<<std::endl;
        fichierCompt << compte.solde<<std::endl;
        fichierCompt << compte.dateCreation<<std::endl;
        fichierCompt <<std::endl<<std::endl;

        return true;
}
}


bool CreTransaction(int numCompt, std::string dates, std::string tipe, int montant, std::string fichierTrans)
{
     ofstream fichierTransac(fichierTrans.c_str(), ios::app);

    //if(!fichierClient) fichierClient(cheminFichier.c_str());

    if(!fichierTransac) return false;
    else
    {
        fichierTransac << numCompt<<std::endl;
        fichierTransac << dates <<"\t"<<tipe <<"\t"<<montant<<std::endl;

        return true;
    }
}


std::string RecuperTrans(int numCompt,std::string fichierTrans)
{

//ifstream lireFichierClient(fichierClient.c_str());
    //ifstream lireFichierCompt(fichierCompt.c_str());
    ifstream lireFichierTrans(fichierTrans.c_str());

    //string copieClient("CopieClient.txt");
    //string copieCompt("CopieCompt.txt");
    string copieTrans("CopieTrans.txt");
    string ligneLu;
    //int const nbrLigneAsauter(7);
    //int nbrLigneLu(0);
    //int i(0);
    std::string transac("");

    if(!lireFichierTrans) return transac;
    else{
           // bool clientTrouve(false);
        while(getline(lireFichierTrans,ligneLu))
        {

                if(cInt(ligneLu)==numCompt)
                {
                    getline(lireFichierTrans,ligneLu);
                    transac+= transac + ligneLu + "\n";

                }

        }

        }

        return transac;
    }


int cInt(string ch)
{
    int longueur= ch.length();
    const char* chAux(ch.c_str());
    int i(0), nbr(0),j;
    char entier[10];
    //for(i=0 ; i<10 ; i++) entier[i]=i;
    entier[0]='0';entier[1]='1';entier[2]='2';entier[3]='3';entier[4]='4';
    entier[5]='5';entier[6]='6';entier[7]='7';entier[8]='8';entier[9]='9';

    if(!(isNumeric(ch))) return 0;

    for(i=0; i<longueur ; i++)
    {
        //nbr+=chAux[i]*nDizaine(longueur-i-1);
        for(j=0 ; j<=9 ; j++)
        {
            if(chAux[i]==entier[j])
            {
                nbr+=j*nDizaine(longueur-1-i);
            }
        }
    }
    return nbr;
}

int nDizaine(int n)
{
    int i(0),nbr(1);

    if(n==0) return 1;
    else{
        for(i=0 ; i<n ; i++) nbr*=10;
        return nbr;
    }
}

bool isNumeric(string ch)
{
    int lon=ch.length(),i,j;
    const char* chAux(ch.c_str());
    bool ok(true);
    char entier[10];
    //for(i=0 ; i<10 ; i++) entier[i]=i;
    entier[0]='0';entier[1]='1';entier[2]='2';entier[3]='3';entier[4]='4';
    entier[5]='5';entier[6]='6';entier[7]='7';entier[8]='8';entier[9]='9';
    for(i=0 ; i<lon ; i++)
    {
        bool okAux(false);
        for(j=0 ; j<=9 ; j++)
        {
            if(chAux[i]==entier[j]) okAux=true;
        }
        if(!okAux)
        {
            cout <<ch<<" n'est numerique a cause de "<<chAux[i]<<endl;
            return false;
        }
    }
    cout <<ch<<" est numerique"<<endl;
    return ok;

}



