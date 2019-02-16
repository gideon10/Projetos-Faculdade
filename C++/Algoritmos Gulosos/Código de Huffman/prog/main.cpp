#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

class Node
{
private:
    char character;
    int freq;

public:
    Node *left;
    Node *right;

    Node(){freq=0; left=right=0;}
    void setChar(char character){this->character= character;}
    void setFrequency(int freq){this->freq= freq;}
    char getChar()const{return character;}
    int getFrequency()const{return freq;}
    bool operator > (const Node &x)const{return (this->freq > x.freq);}
};

Node *root;
unordered_map<char, string> *dictionary;

priority_queue<Node, vector<Node>, greater<Node> >* countFrequencies(string &text)
{
    int freq[256];
    priority_queue<Node, vector<Node>, greater<Node> > *pq= new priority_queue<Node, vector<Node>, greater<Node> >();

    for(int i=0; i<256; freq[i]=0,i++);

    for(int i=0; i<text.size(); i++) // Conta frequência de cada caractere
        freq[(int)text[i]]++;

    for(int i=0; i<256; i++)
    {
        if(freq[i] > 0)
        {
            Node obj;
            obj.setChar((char)i);
            obj.setFrequency(freq[i]);
            pq->push(obj);
        }
    }

    return pq;
}

Node* huffman(priority_queue<Node, vector<Node>, greater<Node> > *pq)
{
    while(true)
    {
        Node a= pq->top();
        pq->pop();
        Node b= pq->top();
        pq->pop();

        root= new Node();
        root->setChar('+');
        root->setFrequency(a.getFrequency() + b.getFrequency());
        root->left= (&((*new Node()) = a));
        root->right= (&((*new Node()) = b));

        if(pq->empty())
        {
            delete pq;
            return root;
        }
        pq->push(*root);
    }

}

template <typename Type>
void fillDictionary(Type &dictionary, Node &root,string code)
{
    if(!root.left && !root.right)
    { // é folha
        dictionary[root.getChar()]= code;
        return;
    }

    fillDictionary(dictionary, (*root.left), code + "0");
    fillDictionary(dictionary, (*root.right), code + "1");
}

void createDictionary()
{
    dictionary= new unordered_map<char, string>();
    fillDictionary(*dictionary, *root, "");
}

string * encode(string &text)
{
    huffman(countFrequencies(text)); // cria árvore
    createDictionary();
    string *coded_text= new string();

    for(char ch : text)
        coded_text->append((*dictionary)[ch]);

    return coded_text;
}

string * decode(string &coded_text)
{
    Node *aux= root;
    string *decoded_text= new string();

    for(char ch : coded_text)
    {
        if(ch == '0')
            aux= aux->left;
        else
            aux= aux->right;

        if(!aux->left && !aux->right)
        {
            decoded_text->push_back(aux->getChar());
            aux= root;
        }
    }

    return decoded_text;
}

void printDictionary()
{
    cout<<"\nDicionário gerado:\n";

    for(auto it= dictionary->begin(); it != dictionary->end(); it++)
       cout<<"("<<it->first<<"  -  "<<it->second<<")\n";
}

void deleteTree(Node *root)
{
    if(root)
    {
        deleteTree(root->left);
        deleteTree(root->right);

        delete root;
        root=0;
    }
}


int main()
{
    string text;
    int option=0;



    cout<<" ------------------ CÓDIGO DE HUFFMAN -------------------- \n\n";
    do
    {
        cout<<"Escolha uma opção:\n1 - Inserir um texto.\n2 - Sair.\n";
        cin>>option;

        switch(option)
        {
            case 1: cout<<"Insira o texto: ";
                    cin.ignore();
                    getline(cin, text);

                    string *coded_text, *decoded_text;
                    coded_text= encode(text);
                    decoded_text= decode(*coded_text);

                    printDictionary();
                    cout<<"\nTexto de entrada: "<<text<<"\n";
                    cout<<"\nSaída do texto comprimido: "<<(*coded_text)<<"\n";
                    cout<<"\nTexto decodificado: "<<(*decoded_text)<<"\n\n\n";

                    delete coded_text;
                    delete decoded_text;
                    break;

            case 2: option= 2;
                    break;

           default: cout<<"\nOpção inválida, tente novamente!\n\n";
                    break;

        }

    }while(option != 2);

    deleteTree(root);
    if(dictionary)
        delete dictionary;


    return 0;
}
