using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PcapDotNet.Core;
using PcapDotNet.Packets;
using PcapDotNet.Packets.IpV4;
using PcapDotNet.Packets.Transport;
using PcapDotNet.Packets.Ethernet;

namespace SnifferCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Lista urządzeń
            IList<LivePacketDevice> allDevices = LivePacketDevice.AllLocalMachine;

            if (allDevices.Count == 0)
            {
                Console.WriteLine("No interfaces found! Make sure WinPcap is installed.");
                return;
            }

            // Wypisuje urządzenia
            for (int i = 0; i != allDevices.Count; ++i)
            {
                LivePacketDevice device = allDevices[i];
                Console.WriteLine((i + 1) + ". " + device.Description);
                if (device.Description == null)
                {
                    Console.Write((i + 1) + ". " + device.Name);
                    Console.WriteLine(" (No description available)");
                }
            }

            int deviceIndex = 0;
            //wprowadzanie numeru urzadzenia
            do
            {
                Console.WriteLine("Enter the interface number (1-" + allDevices.Count + "):");
                string deviceIndexString = Console.ReadLine();
                if (!int.TryParse(deviceIndexString, out deviceIndex) ||
                    deviceIndex < 1 || deviceIndex > allDevices.Count)
                {
                    deviceIndex = 0;
                }
            } while (deviceIndex == 0);

            PacketDevice selectedDevice = allDevices[deviceIndex - 1];

            // Ustawiamy komunikator do przechwytywania z urządzenia
            using (PacketCommunicator communicator =
                selectedDevice.Open(65536,                                  // portion of the packet to capture
                                                                            // 65536 guarantees that the whole packet will be captured on all the link layers
                                    PacketDeviceOpenAttributes.Promiscuous, // promiscuous mode
                                    1000))                                  // read timeout
            {
                // Filter
                Console.WriteLine("If you want, you can specify filter now");
                using (BerkeleyPacketFilter filter = communicator.CreateFilter(Console.ReadLine()))
                {
                    communicator.SetFilter(filter);
                }

                Console.WriteLine("Listening on " + selectedDevice.Description + "...");
                // przechwytywanie
                communicator.ReceivePackets(0, PacketHandler);
            }

        }

        // Callback function invoked by Pcap.Net for every incoming packet
        private static void PacketHandler(Packet packet)
        {
            IpV4Datagram ip = packet.Ethernet.IpV4;
            UdpDatagram udp = ip.Udp;

            // print ip addresses and udp ports
            Console.WriteLine("Form -> Where " + ip.Source + ":" + udp.SourcePort + " -> " + ip.Destination + ":" + udp.DestinationPort);
        
            Console.WriteLine("Data capture: "+packet.Timestamp.ToString("yyyy-MM-dd HH:mm:ss.fff"));
            Console.WriteLine("Type:         " + packet.Ethernet.EtherType);

            if(packet.Ethernet.EtherType.ToString() == "Arp")
                Console.WriteLine("Protocol type:" + packet.Ethernet.Arp.ProtocolType);
            else if (packet.Ethernet.EtherType.ToString() == "IpV6")
                Console.WriteLine("Protocol:     " + packet.Ethernet.IpV6.NextHeader);
            else
                Console.WriteLine("Protocol:     " + packet.Ethernet.IpV4.Protocol);
            Console.WriteLine("Length:       " + packet.Length);
            Console.WriteLine("Data:         " + packet.Ethernet.Payload);
            Console.WriteLine();
        }
    }
}
