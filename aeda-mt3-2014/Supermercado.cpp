/*
 * Supermercado.cpp
 *
 * Created on: Dec 3, 2014
 *
 */

#include "Supermercado.h"
#include <iostream>
#include <map>

using namespace std;

//A ser implementado pelo estudante!
/*
 * Supermercado.cpp
 *
 * Created on: Dec 3, 2014
 *
 */

#include "Supermercado.h"

/*
 * Supermercado.cpp
 *
 * Created on: Dec 3, 2014
 *
 */

#include "Supermercado.h"

int Cliente::numeroItens() const {

    int num = 0;

    for (auto it = cestos.begin(); it != cestos.end(); it++) {

        num = num + (*it).getItens().size();

    }

    return num;

}

int Cliente::valorItens() const {

    int valor = 0;

    for (auto it = cestos.begin(); it != cestos.end(); it++) {

        stack<Item> itens = (*it).getItens();

        while(!itens.empty()) {

            valor = valor + itens.top().preco;
            itens.pop();
        }

    }

    return valor;

}

int Cliente::trocarItem(Item &novoItem) {

    int i = 0;

    for (auto it = cestos.begin(); it != cestos.end(); it++) {

        stack<Item> temp;

        while(!(*it).empty()) {

            if ((*it).topItem().produto == novoItem.produto && (*it).topItem().preco > novoItem.preco) {

                temp.push(novoItem);
                (*it).popItem();
                i++;

            }

            temp.push(((*it).topItem()));
            (*it).popItem();

        }

        while(!temp.empty()) {

            (*it).pushItem(temp.top());
            temp.pop();

        }

    }

    return i;

}

void Cliente::organizarCestos() {

    for (auto it = cestos.begin(); it != cestos.end(); it++) {

        vector<Item> temp;

        while(!(*it).empty()) {

            temp.push_back((*it).topItem());
            (*it).popItem();

        }

        sort(temp.begin(), temp.end(), aux);

        while(!temp.empty()) {

            (*it).pushItem(temp.back());

            temp.pop_back();

        }

    }

}

vector<string> Cliente::contarItensPorTipo() {

    vector<string> result;
    stack<Item> itens;
    map<string, int> tipos;

    for (auto it = cestos.begin(); it != cestos.end(); it++) {

        itens = (*it).getItens();

        while(!itens.empty()) {

            if (tipos.empty() || tipos.find(itens.top().tipo) == tipos.end()) {

                tipos[itens.top().tipo] = 1;
                itens.pop();

            }else {
                tipos[itens.top().tipo]++;
                itens.pop();
            }

        }

    }

    for (auto &c : tipos) {

        string temp = c.first + " " + to_string(c.second);
        result.push_back(temp);

    }

    return result;
}

int Cesto::novoItem(const Item& umItem) {

    int volume = 0, peso = 0;

    stack <Item> itens1 = getItens();

    while(!itens1.empty()) {

        volume += itens1.top().volume;
        peso += itens1.top().peso;
        itens1.pop();

    }

    if (volume + umItem.volume < max_volume && peso + umItem.peso < max_volume) {
        itens.push(umItem);
        return itens.size();
    }

    return 0;
}

int Cliente::novoItem(const Item &umItem) {

    for (auto it = cestos.begin(); it != cestos.end(); it++) {

        if ((*it).novoItem(umItem) != 0) {

            return cestos.size();

        }

    }

    Cesto newcesto;
    newcesto.pushItem(umItem);
    cestos.push_back(newcesto);
    return cestos.size();
}

int Supermercado::novoCliente(Cliente &umCliente) {

    int min = 0;
    if (umCliente.getIdade() >= 65) {

        if (filaNormal.size() < filaPrioritaria.size()) {

            filaNormal.push(umCliente);
            return filaNormal.size() + filaPrioritaria.size();

        } else {
            filaPrioritaria.push(umCliente);
            return filaNormal.size() + filaPrioritaria.size();
        }

    } else {

        filaNormal.push(umCliente);
        return filaNormal.size() + filaPrioritaria.size();
    }


}

Cliente Supermercado::sairDaFila(string umNomeDeCliente) {

    Cliente c;
    queue<Cliente> temp;

    while(!filaNormal.empty()) {

        if (filaNormal.front().getNome() == umNomeDeCliente) {

            c = filaNormal.front();
            filaNormal.pop();
            continue;

        }

        temp.push(filaNormal.front());
        filaNormal.pop();

    }

    while(!temp.empty()) {

        filaNormal.push(temp.front());
        temp.pop();

    }

    while(!filaPrioritaria.empty()) {

        if (filaPrioritaria.front().getNome() == umNomeDeCliente) {

            c = filaPrioritaria.front();
            filaPrioritaria.pop();
            continue;

        }

        temp.push(filaPrioritaria.front());
        filaPrioritaria.pop();

    }

    while(!temp.empty()) {

        filaPrioritaria.push(temp.front());
        temp.pop();

    }

    if (c.getNome() == umNomeDeCliente)
        return c;

    throw ClienteInexistente(umNomeDeCliente);

}

bool aux(Item i1, Item i2) {
    return i1.peso < i2.peso;
}
