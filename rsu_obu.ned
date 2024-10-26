simple RSU
{
    gates:
        input in;
        output out;
}

simple OBU
{
    gates:
        input in;
        output out;
}


network CityNetwork
{
    submodules:
        rsu: RSU; // declarando o submódulo do tipo RSU
        obu: OBU; // declarando submódulo do tipo OBU

        connections:
        // o gate (porta) out do OBU (carro) vai enviar pro gate (porta) in (input/entrada) do RSU (infraestrutura)
        obu.out --> {  delay = 100ms; } --> rsu.in;
        // o gate in (input/entrada) do OBU (carro) vai receber mensagens do gate out do RSU (infraestrutura)
        obu.in <-- {  delay = 100ms; } <-- rsu.out;
}