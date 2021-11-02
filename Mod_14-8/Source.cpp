#include <iostream>
#include <string>

using namespace std;
const int MaxBranchNum = 26;  // ����������� ���������� �������

// ���������� ���������� 
int j = 1;      // ���������� ����� ������ � �������� ���������
int k = 1;      // ��������� ����� ������ � �������� ���������
string selStr;  // ��������� ������ � �������� ���������

class TrieNode {
public:
    string word;
    int path;  // ������� ��� ��� ��������� ������, ������������ ��� �������� ���������� ����� � ��������� ���������� ������
    int End; // ������, ��������������� ���� ��������
    TrieNode* nexts[MaxBranchNum];

    TrieNode()
    {
        word = "";
        path = 0;
        End = 0;
        memset(nexts, NULL, sizeof(TrieNode*) * MaxBranchNum);
    }

};

class TrieTree {
private:
    TrieNode* root;
public:
    TrieTree();
    ~TrieTree();
    // ���������� ����� � �������
    void insert(string str);
    // ����� ���� � ��������� str � �������
    int search(string str);
    // ������� ������ str
    void Delete(string str);
    void destory(TrieNode* root);
    // ������������� ��� ���� � ������
    void printAll();
    // ������� ����� � ��������� str
    void printPre(string str);
    // ������� ������������ ������ ���� � ��������� str
    void SelectWord(string str);
    // ������� ��� ����� � ������ � ������������������ �������
    void Print(TrieNode* root);
    // ����� �����
    void Select(TrieNode* root);
    // ���������� ���������� ���� � ��������� str
    int prefixNumbers(string str);
};

TrieTree::TrieTree()
{
    root = new TrieNode();
}


TrieTree::~TrieTree()
{
    destory(root);
}

void TrieTree::destory(TrieNode* root)
{
    if (root == nullptr)
        return;
    for (int i = 0; i < MaxBranchNum; i++)
    {
        destory(root->nexts[i]);
    }
    delete root;
    root = nullptr;
}


void TrieTree::insert(string str)
{
    if (str == "")
        return;
    char buf[sizeof(str)];
    strcpy_s(buf, str.c_str());
    TrieNode* node = root;
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        index = buf[i] - 'a';
        if (node->nexts[index] == nullptr)
        {
            node->nexts[index] = new TrieNode();
        }
        node = node->nexts[index];
        node->path++;// ����� ���� ���� ���� ����
    }
    node->End++;
    node->word = str;
}

int TrieTree::search(string str)
{
    if (str == "")
        return 0;
    char buf[sizeof(str)];
    strcpy_s(buf, str.c_str());
    TrieNode* node = root;
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        index = buf[i] - 'a';
        if (node->nexts[index] == nullptr)
        {
            return 0;
        }
        node = node->nexts[index];
    }
    if (node != nullptr)
    {
        return node->End;
    }
    else
    {
        return 0;
    }
}

void TrieTree::Delete(string str)
{
    if (str == "")
        return;
    char buf[sizeof(str)];
    strcpy_s(buf, str.c_str());
    TrieNode* node = root;
    TrieNode* tmp;
    int index = 0;
    for (int i = 0; i < str.size(); i++)
    {
        index = buf[i] - 'a';
        tmp = node->nexts[index];
        if (--node->nexts[index]->path == 0)
        {
            delete node->nexts[index];
        }
        node = tmp;
    }
    node->End--;
}

int TrieTree::prefixNumbers(string str)
{
    if (str == "")
        return 0;
    char buf[sizeof(str)];
    strcpy_s(buf, str.c_str());
    TrieNode* node = root;
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        index = buf[i] - 'a';
        if (node->nexts[index] == nullptr)
        {
            return 0;
        }
        node = node->nexts[index];
    }
    return node->path;
}
void TrieTree::printPre(string str)
{
    int j = 0;
    if (str == "")
        return;
    char buf[sizeof(str)];
    strcpy_s(buf, str.c_str());
    TrieNode* node = root;
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        index = buf[i] - 'a';
        if (node->nexts[index] == nullptr)
        {
            return;
        }
        node = node->nexts[index];
    }
    Print(node);
}

void TrieTree::SelectWord(string str)
{
    if (str == "")
        return;
    char buf[sizeof(str)];
    strcpy_s(buf, str.c_str());
    TrieNode* node = root;
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
    {
        index = buf[i] - 'a';
        if (node->nexts[index] == nullptr)
        {
            return;
        }
        node = node->nexts[index];
    }
    Select(node);
}


void TrieTree::Print(TrieNode* node)
{
    if (node == nullptr)
        return;
    if (node->word != "")
    {
        cout << j << "   " << node->word << " " << node->path << endl;
        j++;
    }
    for (int i = 0; i < MaxBranchNum; i++)
    {
        Print(node->nexts[i]);
    }
}

void TrieTree::Select(TrieNode* node)
{
    if (node == nullptr)
        return;
    if (node->word != "" && selStr == "")
    {
        if (j == k) {
            selStr = node->word;
            j++;
            return;
        }
        j++;
    }

    if (selStr == "") {
        for (int i = 0; i < MaxBranchNum; i++)
        {
            Select(node->nexts[i]);
        }
    }

}


void TrieTree::printAll()
{
    Print(root);
}


int main()
{
    int nf = 1;
    char symb = ' ';
    string word = "";
    string text = "";
    string selWord = "";

    setlocale(LC_ALL, "");

    TrieTree trie;

//    �������� �������
    string str = "mama";
 //   cout << trie.search(str) << endl;
    trie.insert(str);
    str = "mila";
    trie.insert(str);
    str = "mylo";
    trie.insert(str);
    str = "myla";
    trie.insert(str);
    str = "window";
    trie.insert(str);
    
    cout << "�������: " << endl;
    j = 1;
    trie.printAll();

    while (nf != 0) {
        cout << "�������� ��������: 1 - �������� �����, 2 - ������� �����, 3 - �������� �������, 4 - ���� ������, 0 - �����)" << endl;
        cin >> nf;
        switch (nf) {
        case 0:
            break;
        case 1: 
            cout << "��������: ";
            cin >> str;
            trie.insert(str);
            break;
        case 2:
            cout << "�������: ";
            cin >> str;
            trie.Delete(str);
            break;
        case 3:
            cout << "�������: " << endl;
            j = 1;
            trie.printAll();
            break;
        case 4:
            cout << endl << "��� ����� ������ ����� ����� ������� ������� ����� ������ Enter" << endl;
            cout << "���� � ������� ���� ���������� ����� � ��������� ���������, �� ��� ��������� ��������������� �������" << endl;
            cout << "����� ��������� ��� ��������� �����, ����� ���������� ���� ��� ������ ����� ���������� �����, ����� �������� ��� �������" << endl;
            cout << "��� ���������� ���� �������� _ (�������), ������� ����� ���������� � ������ �������� " << endl;
            cout << "����� ������� ��������� ������ ������, ���� ������ < Enter" << endl;
            cout << "��� ���������� ������ �������: # Enter" << endl;
            cout << endl << "������� �����: " << endl;

            while (symb != '#')
            {
                cin >> symb;
                if (symb == '<')
                {
                    word.erase(word.size() - 1);
                    j = 1;
                    selStr = "";
                }
                if (symb == '_')
                {
                    text += word;
                    text += " ";
                    word = "";
                    j = 1;
                    selStr = "";
                }

                if (symb > '0' && symb <= '9') {
                    k = symb - '0';
                    j = 1;
                    trie.SelectWord(word);
                    word = selStr;

                }
                if (symb >= 'a' and symb <= 'z') {
                    word += symb;

                    cout << trie.prefixNumbers(word);

                    if (trie.prefixNumbers(word) == 1) cout << " ������� ����������� �����: " << endl;
                    else {
                        if (trie.prefixNumbers(word) > 1 && trie.prefixNumbers(word) < 5) cout << " �������� ����������� �����: " << endl;
                        else cout << " ��������� ����������� �����: " << endl;
                    }
                    j = 1;
                    trie.printPre(word);
                }
                cout << text << word;

            }
            break;
        default:
            break;
        }
    }



    return 0;
}
