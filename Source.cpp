#include<iostream> 
#include<string.h> 
#include<stdlib.h>
#pragma warning(disable : 4996)
using namespace std;

void extraaway();
void last();
int Ziden(char ch);
int Zop(char ch);
int Zdel(char ch);
int Zaces(char * str);
void extraaway();

char op[8] = { '+', '-', '*', '/', '=', '<', '>', '%' };
char del[8] = { '}', '{', ';', '(', ')', '[', ']', ',' };
char *aces[] = { "int", "void", "main", "char", "float" };

int idx = 0, idy = 0, k, opx = 0, opy = 0, dli = 0, wdi = 0, wxid = 0, woper = 0, kdi = 0, liti = 0, ci = 0;
int wdel[20], wop[20], wid[20], l = 0, j;
char xdel[20], xiden[20][20], xop[20][20], aces1[20][20];
char iden[20][20], oper[20][20], delem[20], li[20][20], lit[20], cons[20][20];

void lexanal(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (Ziden(str[i]))
		{
			while (Ziden(str[i]))
			{
				iden[idx][idy++] = str[i++];
			}
			iden[idx][idy] = '\0';
			idx++; idy = 0;
		}
		else
			if (str[i] == '"')
			{
				lit[l++] = str[i];
				for (j = i + 1; str[j] != '"'; j++)
				{
					lit[l++] = str[j];
				}
				lit[l++] = str[j]; lit[l] = '\0';
				strcpy(li[liti++], lit);
				i = j + 1;
			}
			else
				if (Zop(str[i]))
				{
					while (Zop(str[i]))
					{
						oper[opx][opy++] = str[i++];
					}
					oper[opx][opy] = '\0';
					opx++; opy = 0;
				}
				else
					if (Zdel(str[i]))
					{
						while (Zdel(str[i]))
						{
							delem[dli++] = str[i++];
						}
					}
					else
					{
						i++;
					}
	}

	extraaway();
	last();
}
int Ziden(char ch)
{
	if (isalpha(ch) || ch == '_' || isdigit(ch) || ch == '.')
		return 1;
	else
		return 0;
}
int Zop(char ch)
{
	int f = 0, i;
	for (i = 0; i<8 && !f; i++)
	{
		if (ch == op[i])
			f = 1;
	}
	return f;
}
int Zdel(char ch)
{
	int f = 0, i;
	for (i = 0; i<8 && !f; i++)
	{
		if (ch == del[i])
			f = 1;
	}
	return f;
}
int Zaces(char * str)
{
	int i, f = 0;
	for (i = 0; i<5; i++)
	{
		if (!strcmp(aces[i], str))
			f = 1;
	}
	return f;
}
void extraaway()
{
	int i, j;
	for (i = 0; i<20; i++)
	{
		wdel[i] = 0;
		wop[i] = 0;
		wid[i] = 0;
	}
	for (i = 1; i<dli + 1; i++)
	{
		if (wdel[i - 1] == 0)
		{
			xdel[wdi++] = delem[i - 1];
			for (j = i; j<dli; j++)
			{
				if (delem[i - 1] == delem[j])
					wdel[j] = 1;
			}
		}
	}

	for (i = 1; i<idx + 1; i++)
	{
		if (wid[i - 1] == 0)
		{
			strcpy(xiden[wxid++], iden[i - 1]);
			for (j = i; j<idx; j++)
			{
				if (!strcmp(iden[i - 1], iden[j]))
					wid[j] = 1;
			}
		}
	}

	for (i = 1; i<opx + 1; i++)
	{
		if (wop[i - 1] == 0)
		{
			strcpy(xop[woper++], oper[i - 1]);
			for (j = i; j<opx; j++)
			{
				if (!strcmp(oper[i - 1], oper[j]))
					wop[j] = 1;
			}
		}
	}

}
void last()
{
	int i = 0;
	idx = 0;
	for (i = 0; i<wxid; i++)
	{
		if (Zaces(xiden[i]))
			strcpy(aces[kdi++], xiden[i]);
		else
			if (isdigit(xiden[i][0]))
				strcpy(cons[ci++], xiden[i]);
			else
				strcpy(iden[idx++], xiden[i]);
	}



	for (i = 0; i<wdi; i++)
		cout << "\nToken:"<< xdel[i] << " \t is Delimeter.\n";
	for (i = 0; i<woper; i++)
	{
		cout << "\nToken: " << xop[i] << "\t is an Operator.\n";
	}

	for (i = 0; i<idx; i++)
	{
		cout << "\nToken:" << iden[i] << "\t is an Identifier.\n";
	}

	for (i = 0; i<kdi; i++)
	{
		cout << "\nToken:" << aces1[i] << "\t is a Keyword.\n";
	} 
	for (i = 0; i<ci; i++)
	{
		cout << "\nToken:"<< cons[i] << "\t is a Digit. \n";
	}

	for (i = 0; i<liti; i++)
	{
		cout << "\nToken" << li[i] << "\t is a Literal.\n";
	}
}
int main()
{
	char str[50];

	cout << "\nEnter the string : ";
	cin >> str;
	lexanal(str);
	system("pause > 0");
}