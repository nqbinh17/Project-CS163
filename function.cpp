#include "Header.h"

void wordTrie::add(string path)
{
	ifstream fin;
	fin.open(path);
	if (fin)
	{
		wordNode*cur = NULL;
		while (!fin.eof())
		{
			wordNode* cur = NULL;
			int n = 0;
			string word = takeWord(fin, n);
			if (root == NULL) root = new wordNode;
			cur = root;
			for (int i = 0; i < n; i++)
			{

				char x = tolower(word[i]);
				if (x - 'a' >= 26 || x - 'a' < 0)
					break;
				if (cur->children[x - 'a'] == NULL)
				{
					cur->children[x - 'a'] = new wordNode;
				}
				cur = cur->children[x - 'a'];
			}
			if (cur->phead == NULL)
			{
				cur->phead = new pathNode;
				cur->phead->occurance++;
				cur->phead->path = path;
				cur->phead->pnext = NULL;
			}
			else
			{
				pathNode*curpath = cur->phead;
				while (curpath->pnext != NULL&&curpath->path != path)
				{
					curpath = curpath->pnext;
				}
				if (curpath->path == path)
				{
					curpath->occurance++;
				}
				else
				{
					curpath->pnext = new pathNode;
					curpath = curpath->pnext;
					curpath->path = path;
					curpath->occurance++;
				}

			}

		}
	}
	fin.close();
}
bool checkValidation(char x)
{
	if ((x>64 && x<91) || (x>96 && x<123))
		return true;
	return false;
}
string wordTrie::takeWord(ifstream &fin, int &n)
{
	string word, word2, word3;
	char x;
	fin >> x;
	while (!checkValidation(x))fin >> x;
	word += x;
	getline(fin, word2, ' ');
	word3 = word + word2;
	n = word3.length();

	return word3;
}



void wordTrie::printInternal(wordNode*root, string word)
{
	if (root->phead != NULL)
	{
		cout << word << "-";
		pathNode *cur = root->phead;
		while (cur != NULL)
		{
			cout << cur->path << "," << cur->occurance << ";";
			cur = cur->pnext;
		}
		cout << endl;
	}
	for (int i = 0; i < 26; i++)
	{
		if (root->children[i] != NULL)
		{
			word += 'a' + i;
			printInternal(root->children[i], word);
			word.pop_back();
		}
	}
}
void wordTrie::print()
{
	string word;
	printInternal(root, word);
}
bool wordTrie::search(string s, wordNode *root)
{
	int i = 0;
	wordNode * cur = root;
	char x;
	//function filter 
		while (checkValidation(s[i]) && i<s.length())
		{
			if (cur == NULL)return false;
			if (i==s.length()-1 && cur->phead != NULL)return true;
			x = tolower(s[i]);
			cur = cur->children[s[i] - 'a'];
			i++;
		}
		return false;
}

// Binh's
void LinkedList::InsertWords(string s,Node *&cur)
{
	if(cur==NULL)
	{
		cur=new Node;
		cur->s=s;
		return;
	}
	else InsertWords(s,cur->next);
	return;
}
void LinkedList::RunInsertWords(string s)
{
	InsertWords(s,head);
}


void StopWordChaining::RuncreateChaining()
{
	ifstream fin;

	fin.open("Stopwords.txt");
	if(!fin.good())
	{
		cout<<" Stopword.txt ERROR!!";
		exit(1);
	}
	while(!fin.eof())
	{
		string s;
		getline(fin,s,'\n');
		fin.ignore(100,'\n');
		int t=s.length(),index=0;
		for(int i=0;i<t;i++)
		{
			index+=s[i];
		}
		index=index%419;
		arr[index].RunInsertWords(s);
	}


	fin.close();
	return;
}
