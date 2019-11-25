
// #include <iostream>
// #include <boost/asio.hpp>
// #include <boost/array.hpp>

// using boost::asio::ip::tcp;

// int main()
// {
//     // Création du service principal et du résolveur.
//     boost::asio::io_service ios;

//     // On veut se connecter sur la machine locale, port 7171
//     tcp::endpoint endpoint(boost::asio::ip::address::from_string("10.41.167.130"), 4242);

//     // On crée une socket // (1)
//     tcp::socket socket(ios);

//     // Tentative de connexion, bloquante // (2)
//     socket.connect(endpoint);

//     // Création du buffer de réception // (3)
//     boost::array<char, 128> buf;
//     while (1)
//     {
//         boost::system::error_code error;
//         // Réception des données, len = nombre d'octets reçus // (4)
//         int len = socket.read_some(boost::asio::buffer(buf), error);

//         if (error == boost::asio::error::eof) // (5)
//         {
//             std::cout << "\nTerminé !" << std::endl;
//             break;
//         }

//         // On affiche (6)
//         std::cout.write(buf.data(), len);
//     }

//     return 0;
// }

#include <QtCore/QCoreApplication>

#include "QtClient.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpSocket s;
    s.doConnect();

    return a.exec();
}