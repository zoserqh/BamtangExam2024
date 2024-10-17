#include<iostream>
using namespace std;

char freqLang[] = "TEOAISRHNUCMDLGWFPYKJBVQX";
char message[] = 
    "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\n"
    "Xof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF\n"
    "HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\n"
    "Zgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\n"
    "Xof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz\n"
    "dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon\n"
    "Rdepdrw.\n"
    "(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n"
    "(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)\n\0";

void decryptMessage(char* message, char* freqLang);

int main() {
	cout << "message:\n" << message << "\n" << "freqLang: " <<freqLang << endl;
    decryptMessage(message, freqLang);
}

void decryptMessage(char* message, char* freqLang) {
    int alphabetSize = 26;
	int freqLetter[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char freqLangLetter[alphabetSize];

	// reading the message element by element to create the histogram
	int pos0 = 0;
	while (message[pos0] != '\0') {
		if (message[pos0] > 64 && message[pos0] < 91) {  // uppercase
			int pos1 = message[pos0] - 65;
			freqLetter[pos1]++;
		}
		if (message[pos0] > 96 && message[pos0] < 123) { // lowercase
			int pos1 = message[pos0] - 97;
			freqLetter[pos1]++;
		}
		//ignored non-alphabetic characters
		pos0++;
	}

	cout << "\n---------------------------------------\n";
	cout << "histogram:";
	for (int i=0; i < alphabetSize; i++) {
		cout << freqLetter[i] << " ";
	}
	cout << endl;

	//using the histogram to create freqLangLetter from higher to lower frequency
	int pos2 = 0;
	int valueMaxLimit = 0;
	for (int i = 0; i < alphabetSize; i++) {
		if (freqLetter[i] > valueMaxLimit) {
			valueMaxLimit = freqLetter[i];
			pos2 = i;
		}
	}
	freqLangLetter[0] = pos2 + 65;
	
	for (int i = 1; i < alphabetSize; i++) {	
		int valueCurrMax = 0;
		for (int j = 0; j < alphabetSize; j++) {
			if (freqLetter[j] >= valueCurrMax && freqLetter[j] < valueMaxLimit) {
				valueCurrMax = freqLetter[j];
				pos2 = j;
			}
		}
		valueMaxLimit = valueCurrMax;
		freqLangLetter[i] = pos2 + 65;
	}
	
	cout << "frequence of alphabetic characters of the message: ";
	for (int i = 0; i < alphabetSize; i++) {
		cout << freqLangLetter[i];
	}
	cout << "\n---------------------------------------\n\n";

	//print the message decrypted using freqLang and freqLangLetter
	cout << "decrypted message: \n";
    int pos3 = 0;
	while (message[pos3] != '\0'){
		if (message[pos3] > 64 && message[pos3] < 91) { //uppercase
			char target = message[pos3];
			for (int i = 0; i < 26; i++) {
				if (freqLangLetter[i] == target) {
					cout << char(freqLang[i]);
				}
			}
		}
		else if (message[pos3] > 96 && message[pos3] < 123) {
			char target = message[pos3]-32;
			for (int i = 0; i < 25; i++) {
				if (freqLangLetter[i] == target) {  //lowercase
					cout << char(freqLang[i]+32);
				}
			}
		}
		else {	//non-alphabetic character
			cout << message[pos3];
		}
		pos3++;
	}
}