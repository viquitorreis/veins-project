#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

// classe RSU vai definir / assinar os métodos referentes ao RSU
class RSU: public cSimpleModule
{
    protected:
    // Função virtual redefinida que vai conter os algoritmos implementados.
        virtual void handleMessage(cMessage *msg) override;
};

class OBU: public cSimpleModule
{
    protected:
        // função virtual que vai inicializar tudo. É chamada só na inicialização do programa
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

// Precisamos registrar os módulos com o omnetpp
Define_Module(RSU);
Define_Module(OBU);

void OBU::initialize()
{
    // o método initialize é chamado no começo da simulação para fazer o bootstrap da simulação
    // um dos módulos precisa enviar a mensagem primerio

    if (strcmp("obu", getName()) == 0) {
        // vai criar e enviar a primeira mensagem no gate "out"
        // uma string qualquer pode ser definida como 'nome' do tipo da mensagem dentro do objeto
        // instanciado cMessage
	    // std::string messageName = "InfoRequest_" + std::to_string(getIndex());
        // cMessage *msg = new cMessage(messageName.c_str());
	    // // precisamos checar se o gate do OBU já está conectado, se não vai bugar
	    // // https://doc.omnetpp.org/omnetpp4/api/classcGate.html#a458a23f084b6e561598cee4876dd3669
        // if (!gate("out")->isConnectedOutside()) {
		//     send(msg, "out");
        // } else {
        //     EV << "Gate 'out' já  está conectado.\n";
        // }
        if (strcmp("obu", getName()) == 0) {
            cMessage *msg = new cMessage("InfoRequest");
            send(msg, "out");
        }
    }
}

void OBU::handleMessage(cMessage *msg)
{
    // o método handleMessage() é chamado sempre que um mensagem chega naquele módulo específico
    // nós só enviamos para outro módulo, através do gate 'out'.
    // no caso
    // send(msg, "out");
    EV << "Mensagem recebida pelo OBU: " << msg->getName() << "\n";
    delete msg; // limpando a mensagem depois de processar ela

    cMessage *response = new cMessage("TouristInfoResponse");
    send(response, "out");
}

// RSU vai processar a requisição (mensagem do OBU) e então vai enviar a resposta
void RSU::handleMessage(cMessage *msg)
{
    EV << "RSU recebeu a requisição: " << msg-> getName() << "\n";
    delete msg; // limpando a mensagem recebida

    // cria e envia a resposta de volta para o OBU
    // cMessage *response = new cMessage("TouristInfoRespose");
    // send(response, "out", 0);

    // iterando pelos OBUs
    // for (int i = 0; i < getParentModule()->par("numOBUs").intValue(); i++) {
    //     std::string obuPath = "CityNetwork.obu[" + std::to_string(i) + "]";
    //     cModule *obuModule = getSimulation()->getModuleByPath(obuPath.c_str());

    //     if (obuModule) {
    //         cMessage *response = new cMessage("TouristInfoResponse");
    //         send(response, "out", i); // enviando no gateway array out[i]
    //     }
    // }

    // getParentModule() -> https://doc.omnetpp.org/omnetpp/api/classomnetpp_1_1cModule.html#a6273eb514331e0e44130844d637b8b4c
    EV << "[numOBUs]: " << getParentModule()->par("numOBUs").intValue() << "\n";
    for (int i = 0; i < getParentModule()->par("numOBUs").intValue(); i++) {
        cMessage *response = new cMessage("TouristInfoResponse");
        send(response, "out", i); // enviando via gate array out[i]
    }
}
