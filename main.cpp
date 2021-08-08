/*
  Roco's default kart editor. Based on Ermelber's, MKDasher's and Yami's
  MKDS ARM9 Music Table Editor 1.0
*/


#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <streambuf>
#include <cerrno>
#include <cstdlib>
#include <ctype.h>

using namespace std;

string get_file_contents(const char *filename) {
	ifstream in (filename, ios::in | ios::binary);
	if (in) {
		ostringstream contents;
		contents << in.rdbuf();
		in.close();
		
		return (contents.str());
	}  else {
				cout << "There isn't a valid file called ''arm9.bin'' in your directory.\nCheck if it really is there.\n";
				cin.ignore();			
				exit(1);
			}
}

int min(int a, int b){
 if (a < b) return a;
 else return b;
}

int main() {
    const int offset = 1389172;
    int selected;
    int newvalue;
    char choice;
    string chars[13];
    int a[211];
    chars[0] = "Mario";
    chars[1] = "DK";
    chars[2] = "Toad";
    chars[3] = "Bowser";
    chars[4] = "Peach";
    chars[5] = "Wario";
    chars[6] = "Yoshi";
    chars[7] = "Luigi";
    chars[8] = "Dry Bones";
    chars[9] = "Daisy";
    chars[10] = "Waluigi";
    chars[11] = "ROB";
    chars[12] = "Shy Guy";
    //Start
    printf("Roco's default kart editor\n\nSpecial thanks to Ermelber, Yami and MKDasher, without them this wouldn't be possible\nPress enter to continue\n\n");
    cin.ignore();    
    //Get arm9.bin
    string text = get_file_contents("arm9.bin");
    for (int i = offset; i < min(text.size(), offset + 211); i++)
        a[i-offset] = (int) text[i];       
    do
    {
        //Print Tracks       
        for (int i = 0; i < 13; i++){
            cout << i << ") "<< chars[i] <<" [" << a[i*4] <<"]" << endl;
        }
        //Select slot
        do{
            printf("\n\nSelect a character to change [0..12]: ");
            scanf("%d",&selected);        
        }while (selected <0 || selected>12); 
    
        //Confirm
        while (true) {
            cout << "\nDo you want to change " << chars[selected] << " default kart? [Y/N] ";
            cin >> choice;
        //Choices
            if ((choice == 'Y') || (choice == 'y')) {
                do{
                    //New value
                    printf("If you want to know what kart id you should put, please visit: https://bit.ly/3fHDHNi\nNote:Kart ID 36 will crash the game.\n");
                    cout << "\nInsert the new kart id (Old value was " << a[selected*4] << ") [0..36]=";
                    scanf("%d",&newvalue);
                }while (newvalue <0 || newvalue>36);
                a[selected*4]=newvalue;
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    
        
        while (true) {
            cout << "\nDo you want to edit it furthermore? [Y/N] ";
            cin >> choice;

            if ((choice == 'Y') || (choice == 'y')) {
                break;
            }
            else if ((choice == 'N') || (choice == 'n')) {
                break;
            }
            else {
                cout << "\nThe Choice isn't valid.";
            }
        }
    }
    while (choice == 'Y' || choice == 'y'); 
    
    /*//Prints array (Testing purposes)
    for (int i=0; i<211; i++)
        cout << a[i] << endl;
    cin.ignore();*/
    
    //Make backup and overwrite arm9.bin
    ofstream out( "arm9.bin.bak", std::ios_base::binary | std::ios_base::out );
    out << text;
    out.close();
    for (int i = offset; i < min(text.size(), offset + 211); i++)
        text[i] = a[i-offset];    
    out.open( "arm9.bin", std::ios_base::binary | std::ios_base::out );
    out << text;
    out.close();
    	
	cout << "\nSuccessfully saved edited_arm9.bin in your folder!\nPress ENTER to exit the program :3\n";
    cin.ignore();
    cin.ignore();    
    //end
    return 0;
}
