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
        cMessage *msg = new cMessage("InfoRequest");
        send(msg, "out");
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
}

// RSU vai processar a requisição (mensagem do OBU) e então vai enviar a resposta
void RSU::handleMessage(cMessage *msg)
{
    EV << "RSU recebeu a requisição: " << msg-> getName() << "\n";
    delete msg; // limpando a mensagem recebida

    // cria e envia a resposta de volta para o OBU
    cMessage *response = new cMessage("TouristInfoRespose");
    send(response, "out");
}
