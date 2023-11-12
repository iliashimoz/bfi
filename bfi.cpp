// BrainFuck Interpreter (BFI) v1.0

#include <fstream>
#include <iostream>

constexpr int memSize = 65536;

int memory[memSize];
int pointer = 0;

void Interpret(char* listing, int length)
{
	int i = 0;
	while (i < length)
	{
		char op = listing[i];
		switch (op)
		{
		case 43:
			memory[pointer]++;
			i++;
			break;
		case 45:
			memory[pointer]--;
			i++;
			break;
		case 62:
			pointer++;
			if (pointer >= memSize) pointer -= memSize;
			i++;
			break;
		case 60:
			pointer--;
			if (pointer < 0) pointer += memSize;
			i++;
			break;
		case 46:
			putchar(memory[pointer]);
			i++;
			break;
		case 58:
			std::cout << memory[pointer] << std::endl;
			i++;
			break;
		case 44:
		{
			int c = 0;
			std::cin >> c;
			memory[pointer] = char(c);
			i++;
		}
			break;
		case 91:
		{
			int nested = 0;
			int j = i;
			int k = 0;
			int p = pointer;
			char* text = new char[length];
			j++;
			while (nested > -1)
			{
				if (listing[j] == 91) nested++;
				if (listing[j] == 93) nested--;
				text[k] = listing[j];
				k++; j++;
			}
			char* cycleBody = new char[k];
			for (int l = 0; l < k - 1; l++) cycleBody[l] = text[l];
			delete[] text;
			while (memory[p] != 0) Interpret(cycleBody, k - 1);
			i = j;
		}	
			break;

		default:
			std::cout << "Unexpected operator in " << i << " position!" << std::endl;
			i++;
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	char* text = new char[memSize];
	if (argc != 1)
	{
		system("cls");
		char* filename = argv[1];
		int length = 0;
		while (filename[length] != 0) length++;
		int p = 0;
		for (int i = 0; i < length; i++) if (filename[i] == 46) p = i;
		if ((filename[p + 1] == 98 or filename[p + 1] == 66) and (filename[p + 2] == 102 or filename[p + 2] == 70))
		{
			std::ifstream inStream;
			char op;
			int i = 0;
			inStream.open(filename);
			char* text = new char[memSize];
			while (inStream >> op) if (op != 10) text[i++] = op;
			char* listing = new char[i];
			for (int j = 0; j < i; j++) listing[j] = text[j];
			inStream.close();
			delete[] text;
			std::cout << "BrainFuck Interpreter v1.0" << std::endl;
			std::cout << "##########################\n" << std::endl;
			std::cout << "File: " << filename << std::endl;
			std::cout << "\nResult: ";
			Interpret(listing, i);
			std::cout << "\n##########################\n" << std::endl;
		}
	}
	else
	{
		std::cout << "BrainFuck Interpreter v1.0" << std::endl;
		std::cout << "##########################\n" << std::endl;
		std::cout << ">>> ";
		char op;
		int length = 0;
		std::cin >> text;
		while (text[length] != 0) length++;
		char* listing = new char[length];
		for (int i = 0; i < length; i++) listing[i] = text[i];
		delete[] text;
		Interpret(listing, length);
	}
	system("pause");
	system("cls");
}