# ttop

Interactive and daemon-like utility to analyze, count and log Ethernet traffic. It depends on https://github.com/johnlepikhin/TrafficProcessor - deep traffic analyzing library which provides statistical and concrete information starting from Ethernet frames up to HTTP headers content. It receives frames from PCAP, can consolidate frames into TCP sessions, works well in high packet loss sessions.

## Modes

 1. 'top'. Ncurses-based, top-like view on requested counters
 2. 'dump'. Raw view with customizable field and record sepsrators with file or STDOUT as possible destinations.
 
## Usage

```
ttop  [-p] [-i <file>] [-c <file>] [--] [--version] [-h]


Where: 

   -p,  --help-parsers
     Print available parsers and exit

   -i <file>,  --input <file>
     Path to input file (use '-' for STDIN, this is default) or use format
     iface:eth0 to gather data from specified interface

   -c <file>,  --config <file>
     Path to config file
     Displays usage information and exits.
```

The key features are accessible via configuration file

## Configuration file

Base template:

    <?xml version="1.0" ?>
    <ttop>
       <parsers>
          ... parsers and views ...
       </parsers>
    </ttop>

```<parsers>``` is root parser of parsing tree and provides information to very basinc EtherNet frames. At every level traffic information can be retrieved with ```<view>```'s:

    <?xml version="1.0" ?>
    <ttop>
      <parsers>
        <view>
           ... view configuration ...
        </view>
       </parsers>
    </ttop>

Similarly, one can view traffic at every level, as many times as required:

    <?xml version="1.0" ?>
    <ttop>
      <parsers>
        <view>
           ... view configuration ...
        </view>
        <parser of="DIX">
          <parser of="IPv4">
            <view>
              ... view configuration for IPv4 frames ...
            </view>
          </parser>
        </parser>
       </parsers>
    </ttop>

### Valid hierarchy of parsers

Parsers hierarchy is very specific:

```(root)
  DIX
  RAW
  802LLC
  SNAP

DIX
  IPv4
  IPv6
  
802LLC
  IPv4
  IPv6
  
SNAP
  IPv4
  IPv6
  
RAW
  IPv4
  IPv6
  
IPv4
  IPv4Packet
  
IPv4Packet
  TCP
  UDP
  
TCP
  TCPSession
  
TCPSession
  HTTP
  MySQL
  SSL
```

(to be continued)

I.e. parser "TCPSession" can be followed by parsers of "HTTP", "MySQL" and "SSL", but not by parser of "IPv6".

### Views

```<view>``` is SQL-like query language. For example, every second output to STDOUT UNIX time, source and destination MAC addresses, number of matched frames, total length of captured by PCAP bytes and total declared length of matched frames, group by source+destination MAC address:

    <view type="dump" output="-">
      <select>
        <long2string name="seconds"><Seconds/></long2string>
        <SourceMAC name="source"/>
        <DestinationMAC name="dest"/>
        <long2string  name="counter"><counter/></long2string>
        <long2string order="numeric" name="captured"><sum><Captured/></sum></long2string>
        <long2string name="length"><sum><Length/></sum></long2string>
      </select>
      <trigger timeInterval="1">
        <false/>
      </trigger>
      <groupBy>
        <concat>
          <SourceMAC/>
          <DestinationMAC/>
        </concat>
      </groupBy>
    </view>

Check for more examples on Github's repository page.
