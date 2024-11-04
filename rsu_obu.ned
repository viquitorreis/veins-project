// simple RSU
// {
//     gates:
//         input in[numOBUs]; // gate 'in' vai ser um vetor de inputs
//         output out[numOBUs];
// }

// simple OBU
// {
//     gates:
//         input in;
//         output out;
// }

// network CityNetwork
// {
//     // submodules:
//     //     rsu: RSU; // declarando o submódulo do tipo RSU
//     //     obu[numOBUs]: OBU; // declarando submódulo do tipo OBU

//     //     connections:
//     //     // o gate (porta) out do OBU (carro) vai enviar pro gate (porta) in (input/entrada) do RSU (infraestrutura)
//     //     // obu.out --> {  delay = 100ms; } --> rsu.in;
//     //     // o gate in (input/entrada) do OBU (carro) vai receber mensagens do gate out do RSU (infraestrutura)
//     //     // obu.in <-- {  delay = 100ms; } <-- rsu.out;
//     //     	for i=0..sizeof(obu)-1 {
//     //     	    obu[i].out --> { delay = 100ms; } --> rsu.in[i]; // conectando cada OBU a um gate 'in' unico
//     //     	    obu[i].in <-- { delay = 100ms; } <-- rsu.out[i];
//     //     	}
//     parameters:
//         int numOBUs = default(5); // Default value if not set elsewhere

//     submodules:
//         rsu: RSU;
//         obu[numOBUs]: OBU;
    
//     connections allowunconnected:
//         for i=0..numOBUs-1 {
//             obu[i].out --> { delay = 100ms; } --> rsu.in[i];
//             obu[i].in <-- { delay = 100ms; } <-- rsu.out[i];
//         }
// }

simple RSU
{
    parameters:
        int numOBUs;
    gates:
        input in[numOBUs];
        output out[numOBUs];
}

simple OBU
{
    gates:
        input in;
        output out;
}

network CityNetwork
{
    parameters:
        int numOBUs = default(5);

    submodules:
        rsu: RSU {
            parameters:
                numOBUs = numOBUs;
        }
        obu[numOBUs]: OBU;
    
    connections allowunconnected:
        for i = 0..numOBUs-1 {
            obu[i].out --> { delay = 500ms; } --> rsu.in[i];
            obu[i].in <-- { delay = 500ms; } <-- rsu.out[i];
        }
        // for i=0..numNodes-1 {
        //     rsu.out --> { delay = 100ms; } --> obu[i].in;
        //     obu[i].out --> { delay = 100ms; } --> rsu.in;
        // }
}

