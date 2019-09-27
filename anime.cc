/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes1,nodes2;
  nodes1.Create (2);
  nodes2.Add(nodes1.Get(1));
  nodes2.Create(1);

  PointToPointHelper pointToPoint,ptp2;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
  ptp2.SetDeviceAttribute ("DataRate", StringValue ("7Mbps"));
  ptp2.SetChannelAttribute ("Delay", StringValue ("1ms"));

  NetDeviceContainer devices1,d2;
  devices1 = pointToPoint.Install (nodes1);
  d2 = ptp2.Install(nodes2);

  InternetStackHelper stack;
  stack.Install (nodes1);
  stack.Install (nodes2.Get(1));

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  
  Ipv4AddressHelper address1;
  address1.SetBase ("10.2.2.0", "255.255.255.0");
  

  Ipv4InterfaceContainer interfaces1 = address.Assign (devices1);
  Ipv4InterfaceContainer interfaces2 = address1.Assign (d2);

  UdpEchoServerHelper echoServer1(9),echoServer2(10);

  ApplicationContainer serverApps1 = echoServer1.Install (nodes1.Get (1));
  serverApps1.Start (Seconds (1.0));
  serverApps1.Stop (Seconds (10.0));

  ApplicationContainer serverApps2 = echoServer2.Install (nodes2.Get (0));
  serverApps2.Start (Seconds (1.0));
  serverApps2.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces1.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  UdpEchoClientHelper echoClient2 (interfaces2.GetAddress (0), 10);
  echoClient2.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient2.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps1 = echoClient.Install (nodes1.Get (0));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));

  ApplicationContainer clientApps2 = echoClient2.Install (nodes2.Get (1));
  clientApps2.Start (Seconds (2.0));
  clientApps2.Stop (Seconds (10.0));

  AnimationInterface anim("anim1.xml");
  anim.SetConstantPosition(nodes1.Get(0),1.0,2.0);
  anim.SetConstantPosition(nodes1.Get(1),34.5,3.0);
  anim.SetConstantPosition(nodes2.Get(1),69.5,4.0);
  anim.EnablePacketMetadata(true);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
