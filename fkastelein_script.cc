/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-module.h"

// Default Network Topology
//
// Number of wifi nodes can be increased up to 250
//                          |
// -------------------------
//   Wifi 10.1.1.0
//                 AP
//  *    *    *    *
//  |    |    |    |
// n5   n6   n7   n0
//


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("fkastelein");

int main (int argc, char *argv[])
{
    bool movingNodes = false;
    bool showNodePositions = false;
    uint32_t nWifi = 1;
    uint32_t packetSize = 1024;
    uint32_t mode = 1;
    double initialRadius = 40;
    double maxRadius = 79;

    // Default file to write
    char fileName[100];
    sprintf( fileName, "Temp.txt" );
    
    // Default Datarate
    double dataRateSetting = 11;
    StringValue dataRate = StringValue("DsssRate11Mbps");
    
    // Read command line arguments
    CommandLine cmd;
    cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
    cmd.AddValue ("dataRateSetting", "1 = 1 Mbps, 2 = 2 Mbps, 5.5 = 5.5M bps, 11 = 11 Mbps", dataRateSetting);
    cmd.AddValue ("fileName", "File to write result to", fileName);
    cmd.AddValue ("packetSize", "packetSize of the UDP message", packetSize);
    cmd.AddValue ("mode", "1 = total througput, 2 = per node througput", mode);
    cmd.AddValue ("showNodePositions", "show the (initially) node positions", showNodePositions);
    cmd.AddValue ("movingNodes", "true = RandomWalk2dMobilityModel, false = ConstantPositionMobilityModel", movingNodes);
    cmd.AddValue ("initialRadius", "initial radius of all the APs from the origin", initialRadius );
    cmd.Parse (argc,argv);
    
    std::cout << "/* Start Initialising Data */" << "\n" << std::endl;
    
    // Set Datarate
    if ( dataRateSetting == 1 )
    {
        std::cout << "Data rate     = DsssRate1Mbps" << std::endl;
        dataRate = StringValue("DsssRate1Mbps");
    }
    else if ( dataRateSetting == 2 )
    {
        std::cout << "Data rate     = DsssRate2Mbps" << std::endl;
        dataRate = StringValue("DsssRate2Mbps");
    }
    else if ( dataRateSetting == 5.5 )
    {
        std::cout << "Data rate     = DsssRate5.5Mbps" << std::endl;
        dataRate = StringValue("DsssRate5_5Mbps");
    }
    else if ( dataRateSetting == 11 )
    {
        std::cout << "Data rate     = DsssRate11Mbps" << std::endl;
        dataRate = StringValue("DsssRate11Mbps");
    }
    
    // Print fileName to write to
    
    if ( packetSize <= 1472 )
    {
        std::cout << "packetSize    = " << packetSize << " bytes" << std::endl;
    }
    else
    {
        std::cout << "packetSize    = " << "ERROR, WRONG VALUE: not [0-1472]" << std::endl;
        return 0;
    }
    
    if ( nWifi )
    {
         std::cout << "nWifi         = " << nWifi << std::endl;
    }
    else
    {
        std::cout << "nWifi          = " << "ERROR, WRONG VALUE: not [1-10]" << std::endl;
        return 0;
    }
   
    std::cout << "fileName      = " << fileName << std::endl;
    std::cout << "movingNodes   = " << movingNodes << std::endl;
    
    
    if ( initialRadius >= 0 && initialRadius <= maxRadius )
    {
        std::cout << "initialRadius = " << initialRadius << std::endl;
    }
    else
    {
        std::cout << "initialRadius = " << "ERROR, WRONG VALUE: not [0-79]" << std::endl;
        return 0;
    }
    
    // Write mode
    if ( mode == 1 )
        std::cout << "mode          = " << "writing (total) throughput" << std::endl;
    else if (mode == 2 )
        std::cout << "mode          = " << "writing (per node) throughput" << std::endl;
    else
        std::cout << "mode          = " << "ERROR, WRONG VALUE" << std::endl;

    // Check for valid number of csma or wifi nodes
    if (nWifi > 250 )
    {
        std::cout << "Too many wifi nodes, no more than 250 each." << std::endl;
        return 1;
    }
    
    std::cout << "\n" << "/* End Initialising Data */" << std::endl;
    
    // Create STA and AP node(s)
    NodeContainer staNodes;
    NodeContainer apNode;
    staNodes.Create(nWifi);
    apNode.Create(1);
    
    // Create WiFi channel and link physical and channel
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
    YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
    phy.SetChannel (channel.Create ());
    
    WifiHelper wifi = WifiHelper::Default ();
    wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
    wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager","DataMode", dataRate, "ControlMode", dataRate);
    
    NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();
    
    // Install devices on the network
    Ssid ssid = Ssid ("ns-3-ssid");
    mac.SetType ("ns3::StaWifiMac",
                 "Ssid", SsidValue (ssid),
                 "ActiveProbing", BooleanValue (false));
    
    NetDeviceContainer staDevices;
    staDevices = wifi.Install (phy, mac, staNodes);
    
    mac.SetType ("ns3::ApWifiMac",
                 "Ssid", SsidValue (ssid));
    
    NetDeviceContainer apDevice;
    apDevice = wifi.Install (phy, mac, apNode);
    
    // Set the mobility and position of the devices
    MobilityHelper mobility;
    
    Ptr<ListPositionAllocator> initialAlloc = CreateObject<ListPositionAllocator>();
    double currentAngle = 0.0;
    const double pi = 3.1415926535897;
    
    if ( showNodePositions )
        std::cout << "/* Start AP Nodes Positions */\n" << std::endl;
    
    // Create N points evenly spaced around the origin with the same radius
    for (uint32_t i = 0; i < staNodes.GetN(); i++ )
    {
        initialAlloc->Add (Vector (i, cos(currentAngle)*initialRadius, sin(currentAngle)* initialRadius ));
        
        if ( showNodePositions )
            std::cout << "AP " << i + 1 << ": ( " << cos(currentAngle)*initialRadius << ", " << sin(currentAngle)* initialRadius << " )" << std::endl;
        
        currentAngle += 2.0*pi/ (double) nWifi;
    }
    
    if ( showNodePositions )
        std::cout << "\n/* Start AP Nodes Positions */" << std::endl;
    
    initialAlloc->Add( Vector ( staNodes.GetN(), 0.0, 0.0 ) );
    
    mobility.SetPositionAllocator(initialAlloc);
    
    if ( movingNodes )
    {
        mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                                   "Distance", ns3::DoubleValue (initialRadius/5.0),
                                   "Bounds", RectangleValue (Rectangle (-maxRadius, maxRadius, -maxRadius, maxRadius)));
    }
    else
        mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

    mobility.Install (staNodes);
    
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (apNode);
    
    InternetStackHelper stack;
    stack.Install (staNodes);
    stack.Install (apNode);
    
    Ipv4AddressHelper address;
    
    address.SetBase ("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer apInterface, staInterfaces;
    staInterfaces = address.Assign (staDevices);
    apInterface = address.Assign (apDevice);
    
    UdpEchoServerHelper echoServer (9);
    ApplicationContainer serverApps = echoServer.Install (apNode.Get (0));
    
    serverApps.Start (Seconds (1.0));
    serverApps.Stop (Seconds (7.0));
    
    double interval = 1.0 / dataRateSetting / 1000.0 / 1000.0 * (double) packetSize * (double) nWifi;
    
    UdpEchoClientHelper echoClient (apInterface.GetAddress (0), 9);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (10000000));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds(interval)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (packetSize));
    
    ApplicationContainer clientApps = echoClient.Install (staNodes);
    clientApps.Start (Seconds (2.0));
    clientApps.Stop (Seconds (7.0));
    
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
    
    Simulator::Stop (Seconds (7.0));
    
    // Init Flowmonitor
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll ();
    
    // Run the simulation
    Simulator::Run ();
    
    // Calculate the Throughput
    monitor->CheckForLostPackets ();
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier());
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
    
    uint64_t bytesTotal = 0;
    double lastRxTime=-1;
    double firstRxTime=-1;
    
    for (std::map<FlowId,FlowMonitor::FlowStats>::const_iterator i=stats.begin();i!=stats.end(); ++i)
    {
        if (firstRxTime < 0)
        {
            firstRxTime = i->second.timeFirstRxPacket.GetSeconds();
        }
        else if (firstRxTime > i->second.timeFirstRxPacket.GetSeconds() )
        {
            firstRxTime = i->second.timeFirstRxPacket.GetSeconds();
        }
        
        if (lastRxTime < i->second.timeLastRxPacket.GetSeconds() )
        {
            lastRxTime = i->second.timeLastRxPacket.GetSeconds();
        }
        
        bytesTotal = bytesTotal + i->second.rxBytes - 28;
    }
    
    double throughput = bytesTotal*8/(lastRxTime-firstRxTime) /1000.0;
    
    std::cout << "/* Start Presenting results */\n" << std::endl;
    
    std::cout << "expected (total) throughput    = " << 1.0 / interval * packetSize / 1000 * nWifi << " Kbps" << std::endl;
    std::cout << "expected (per node) throughput = " << 1.0 / interval * packetSize / 1000 << " Kbps" << std::endl;
    std::cout << "real (total) throughput        = " << throughput << " Kbps" << std::endl;
    std::cout << "real (per node) throughput     = " << throughput / (double) nWifi << " Kbps" << std::endl;
    
    std::cout << "\n/* End Presenting results */" << std::endl;
    
    // Write result to file
    std::ofstream outfile;
    
    char fileNameFinal[100];
    sprintf( fileNameFinal, "Scripts_Frits/%s", fileName );
    outfile.open(fileNameFinal, std::ios_base::app);
    
    if ( mode == 1 ) // Total througput
        outfile << throughput << std::endl;
    else if ( mode == 2 ) // Per Node Througput
        outfile << throughput / (double) nWifi << std::endl;
    else
        std::cout << "ERROR: mode flag set wrong" << std::endl;

    Simulator::Destroy ();
    return 0;
}
