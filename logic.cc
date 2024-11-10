#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <unordered_set>
#include <cstdlib>   // para randomização

using namespace omnetpp;

class RSU : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

private:
    std::vector<std::string> advertisements; // lista de propagandas
    std::unordered_set<int> assignedOBUs; // set para registrar os OBUs que receberam as propagandas
};

class OBU : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// Registrando os módulos com o omnetpp
Define_Module(RSU);
Define_Module(OBU);

void RSU::initialize() {
    // inicializando a lista de propagandas
    advertisements.push_back("Complexo Parque do Sabiá");
    advertisements.push_back("Museu Municipal de Uberlândia");
    advertisements.push_back("Mercado Municipal");
    advertisements.push_back("Center Convention Uberlândia");
    advertisements.push_back("Center Shopping");

    EV << "RSU initialized with " << advertisements.size() << " advertisements.\n";
}

void RSU::handleMessage(cMessage *msg) {
    EV << "RSU recebeu a requisição: " << msg->getName() << "\n";
    delete msg; // removendo a mensagem recebida

    int numOBUs = getParentModule()->par("numOBUs").intValue();

    for (int i = 0; i < numOBUs; i++) {
        // checando se esse OBU já recebeu uma propaganda
        // método .end() vai retornar o iterador para o final do set
        if (assignedOBUs.find(i) != assignedOBUs.end()) {
            EV << "OBU[" << i << "] já recebeu um anúncio. Ignorando...\n";
            continue;
        }

        // Randomicamente selecionando um anúncio para esse OBU
        int randomIndex = rand() % advertisements.size();
        std::string selectedAdvertisement = advertisements[randomIndex];

        // cria e envia a mensagem com a propaganda selecionada
        cMessage *response = new cMessage(selectedAdvertisement.c_str());
        send(response, "out", i);

        // marca o OBU como tendo recebido uma propaganda
        assignedOBUs.insert(i);
        EV << "Enviando anúncio para OBU[" << i << "]: " << selectedAdvertisement << "\n";

    }
}

void OBU::initialize() {
    // só envia a mensagem de requisição se o módulo for um OBU
    if (strcmp("obu", getName()) == 0) {
        cMessage *msg = new cMessage("InfoRequest");
        send(msg, "out");
    }
}

void OBU::handleMessage(cMessage *msg) {
    EV << "Mensagem recebida pelo OBU: " << msg->getName() << "\n";
    // limpando a msg depois de processar
    delete msg;
}
