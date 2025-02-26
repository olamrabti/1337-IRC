#include "Server.hpp"
#include "numericReplies.hpp"

void webPath(Client &client, int client_fd, std::string server_hostname)
{
    std::string sender = "SECBOT";

    const char *messages[] = {
        "✦ SECBOT Web Application Security Learning Path ✦",
        "",
        "【Core Learning Platforms】",
        "⚡ PortSwigger Web Security Academy",
        "   • URL: https://portswigger.net/web-security",
        "   • Comprehensive, free labs and materials",
        "   • Server-side: SQLi, XXE, SSRF, Path Traversal",
        "   • Client-side: XSS, CSRF, CORS, Clickjacking",
        "   • Advanced: JWT, OAuth, GraphQL, Prototype Pollution",
        "",
        "⚡ HackTheBox Academy",
        "   • URL: https://academy.hackthebox.com",
        "   • Structured modules with hands-on labs",
        "   • Web fundamentals to advanced exploitation",
        "",
        "⚡ PentesterLab",
        "   • URL: https://pentesterlab.com",
        "   • Progressive learning badges",
        "   • Essentials → Unix → PCAP → White Badge",
        "   • Real-world vulnerability scenarios",
        "",
        "【Must-Follow YouTube Channels】",
        "⚡ PwnFunction",
        "   • https://youtube.com/@PwnFunction",
        "   • Animated vulnerability explanations",
        "   • Clear, concise technical breakdowns",
        "",
        "⚡ Bug Bounty Reports Explained",
        "   • https://youtube.com/@BugBountyReportsExplained",
        "   • Real-world vulnerability analysis",
        "   • Detailed methodology explanations",
        "",
        "⚡ STÖK & NahamSec",
        "   • https://youtube.com/@STOKfredrik",
        "   • https://youtube.com/@NahamSec",
        "   • Bug bounty methodology",
        "   • Live hacking & tool tutorials",
        "",
        "【Essential Reading & Practice】",
        "⚡ Pentester Land Write-ups",
        "   • https://pentester.land/writeups",
        "   • Bug bounty methodology & reports",
        "",
        "⚡ PortSwigger Daily Swig",
        "   • https://portswigger.net/daily-swig",
        "   • Latest web security news & research",
        "",
        "⚡ Orange's Blog & Challenges",
        "   • Blog: https://blog.orange.tw",
        "   • CTF: https://github.com/orangetw/My-CTF-Web-Challenges",
        "   • Advanced exploitation techniques",
        "",
        "⚡ PicoCTF",
        "   • https://picoctf.org",
        "   • Perfect for beginners",
        "   • Progressive difficulty challenges",
        "",
        "⚡ Beginner's Bug Bounty Guide",
        "   • https://blog.securitybreached.org/2023/08/18/bug-bounty-blueprint-a-beginners-guide",
        "   • Complete methodology & tools guide",
        "",
        "【Recommended Learning Path】",
        "1. Foundations",
        "   • Complete PortSwigger Academy fundamentals",
        "   • Solve PicoCTF web challenges",
        "   • Watch PwnFunction videos",
        "",
        "2. Building Skills",
        "   • Follow PentesterLab badge progression",
        "   • Start HackTheBox Academy modules",
        "   • Practice on beginner bug bounty programs",
        "",
        "3. Advanced Topics",
        "   • Tackle Orange's CTF challenges",
        "   • Study bug bounty write-ups",
        "   • Follow security news and research",
        "",
        "【Essential Tools】",
        "• Burp Suite Community/Pro",
        "• Firefox + Developer Tools",
        "• OWASP ZAP",
        "• Dirsearch/Gobuster",
        "• Nuclei",
        "",
        "Reminder: Always follow platform rules and practice ethically.",
        "Tip: Take detailed notes and document your learning journey!",
        ">>> TYPE 'BACK' TO RETURN TO THE PREVIOUS PAGE. <<< "};

    size_t numMessages = sizeof(messages) / sizeof(messages[0]);

    for (size_t i = 0; i < numMessages; ++i)
    {
        std::string line = messages[i];
        std::string formatted_msg = PRIVMSG_FORMAT(sender, sender, server_hostname, client.getNickname(), line + "\r\n");
        sendReply(client_fd, formatted_msg);
    }
}

void forPath(Client &client, int client_fd, std::string server_hostname)
{
    std::string sender = "SECBOT";

    const char *messages[] = {
        "✦ SECBOT Digital Forensics & Incident Response Path ✦",
        "",
        "【Core Learning Platforms】",
        "⚡ SANS Digital Forensics",
        "   • URL: https://www.sans.org/cyber-security-courses/digital-forensics-essentials",
        "   • Industry standard training",
        "   • Hands-on forensics investigation",
        "   • Incident response procedures",
        "",
        "⚡ TCM Security - Practical Windows Forensics",
        "   • https://academy.tcm-sec.com/p/practical-windows-forensics",
        "   • Windows artifacts analysis",
        "   • Memory forensics",
        "   • Evidence acquisition",
        "",
        "⚡ 13Cubed Videos",
        "   • https://youtube.com/@13cubed",
        "   • Detailed forensics tutorials",
        "   • Tool demonstrations",
        "   • Real case analysis",
        "",
        "【Essential Tools & Resources】",
        "⚡ Memory Forensics - Volatility",
        "   • https://volatilityfoundation.org",
        "   • Memory analysis framework",
        "   • Process analysis",
        "   • Malware detection",
        "",
        "⚡ Disk Forensics",
        "   • FTK Imager: https://accessdata.com/product-download/ftk-imager-version-4-5",
        "   • Autopsy: https://autopsy.com/download",
        "   • The Sleuth Kit: https://sleuthkit.org",
        "",
        "⚡ Network Forensics",
        "   • Wireshark: https://wireshark.org",
        "   • NetworkMiner: https://netresec.com/?page=NetworkMiner",
        "   • Zeek: https://zeek.org",
        "",
        "【Practice Platforms】",
        "⚡ Digital Forensics CTFs",
        "   • Digital Forensics CTF: https://dfir.training",
        "   • Forensics CTF Challenges: https://github.com/frankito-test/forensics-ctf",
        "",
        "⚡ HackTheBox Forensics Challenges",
        "   • https://app.hackthebox.com/challenges/forensics",
        "",
        "【Key Learning Resources】",
        "⚡ DFIR Community Blog",
        "   • https://aboutdfir.com",
        "   • Case studies",
        "   • Tool tutorials",
        "   • Investigation techniques",
        "",
        "⚡ SANS DFIR Blog",
        "   • https://www.sans.org/blog/digital-forensics",
        "   • Expert articles",
        "   • Research papers",
        "",
        "【Recommended Learning Path】",
        "1. Foundations",
        "   • Basic system architecture",
        "   • File systems and data structures",
        "   • Digital evidence handling",
        "   • Basic tool familiarity",
        "",
        "2. Core Skills",
        "   • Memory analysis with Volatility",
        "   • Disk forensics with Autopsy/FTK",
        "   • Network packet analysis",
        "   • Windows/Linux artifacts",
        "",
        "3. Advanced Topics",
        "   • Malware analysis",
        "   • Mobile device forensics",
        "   • Cloud forensics",
        "   • Anti-forensics techniques",
        "",
        "【Certifications Path】",
        "• SANS GCFE (GIAC Certified Forensic Examiner)",
        "• EnCase Certified Examiner (EnCE)",
        "• AccessData Certified Examiner (ACE)",
        "• Certified Computer Forensics Examiner (CCFE)",
        "",
        "【Essential Investigation Areas】",
        "• Windows Registry Analysis",
        "• Browser Forensics",
        "• Email Investigation",
        "• Memory Analysis",
        "• Timeline Analysis",
        "• Log File Analysis",
        "",
        "Tip: Build your own forensics lab for practice!",
        "Reminder: Always maintain proper chain of custody in real investigations.",
        ">>> TYPE 'BACK' TO RETURN TO THE PREVIOUS PAGE. <<< "

    };

    size_t numMessages = sizeof(messages) / sizeof(messages[0]);

    for (size_t i = 0; i < numMessages; ++i)
    {
        std::string line = messages[i];
        std::string formatted_msg = PRIVMSG_FORMAT(sender, sender, server_hostname, client.getNickname(), line + "\r\n");
        sendReply(client_fd, formatted_msg);
    }
}

void pwnPath(Client client, int client_fd, std::string server_hostname)
{
    std::string sender = "SECBOT";

    const char *messages[] = {
        "✦ SECBOT Binary Exploitation & Reverse Engineering Path ✦",
        "",
        "【Core Learning Resources】",
        "⚡ Guyinatuxedo's Pwn Guide",
        "   • URL: https://guyinatuxedo.github.io",
        "   • Comprehensive binary exploitation tutorials",
        "   • Hands-on exploit development",
        "   • Assembly and low-level programming",
        "",
        "⚡ LiveOverflow",
        "   • https://youtube.com/@LiveOverflow",
        "   • Binary exploitation video series",
        "   • CTF challenge walkthroughs",
        "   • Deep technical explanations",
        "",
        "⚡ The Nightmare Exploitation Course",
        "   • https://guyinatuxedo.github.io/intro.html",
        "   • Step-by-step pwn challenges",
        "   • Progressive difficulty",
        "   • Covers multiple exploitation techniques",
        "",
        "【Practice Platforms】",
        "⚡ PWN Challenge Sites",
        "   • PicoCTF: https://picoctf.org",
        "   • HackTheBox: https://app.hackthebox.com/challenges/pwn",
        "   • ROP Emporium: http://ropemporium.com",
        "",
        "【Essential Tools】",
        "⚡ Reverse Engineering",
        "   • Ghidra: https://ghidra-sre.org",
        "   • IDA Pro",
        "   • Binary Ninja",
        "   • Radare2",
        "",
        "⚡ Exploitation Tools",
        "   • GDB (GNU Debugger)",
        "   • Pwntools",
        "   • ROPgadget",
        "   • Checksec",
        "",
        "【Learning Path】",
        "1. Foundations",
        "   • Assembly language basics",
        "   • Memory layout & stack concepts",
        "   • Basic buffer overflows",
        "   • Linux environment setup",
        "",
        "2. Intermediate Skills",
        "   • ROP (Return Oriented Programming)",
        "   • GOT/PLT hijacking",
        "   • Format string vulnerabilities",
        "   • Shellcode development",
        "",
        "3. Advanced Techniques",
        "   • Heap exploitation",
        "   • Advanced ROP techniques",
        "   • Kernel exploitation",
        "   • Advanced anti-debugging",
        "",
        "【Key YouTube Channels】",
        "• LiveOverflow",
        "• 0x41414141",
        "• John Hammond",
        "• VulnHub",
        "",
        "【Recommended Books】",
        "• The Shellcoder's Handbook",
        "• Practical Malware Analysis",
        "• Hacking: The Art of Exploitation",
        "",
        "Tip: Build a dedicated Linux VM for practice!",
        "Reminder: Always practice ethically and legally.",
        ">>> TYPE 'BACK' TO RETURN TO THE PREVIOUS PAGE. <<< "

    };

    size_t numMessages = sizeof(messages) / sizeof(messages[0]);

    for (size_t i = 0; i < numMessages; ++i)
    {
        std::string line = messages[i];
        std::string formatted_msg = PRIVMSG_FORMAT(sender, sender, server_hostname, client.getNickname(), line + "\r\n");
        sendReply(client_fd, formatted_msg);
    }
}

void windowsPentestPath(Client &client, int client_fd, std::string server_hostname)
{
    std::string sender = "SECBOT";
    const char *messages[] = {
        "✦ SECBOT Windows Penetration Testing Learning Path ✦",
        "",
        "【Core Learning Platforms】",
        "⚡ Offensive Security WinEXP",
        "   • URL: https://www.offensive-security.com/winexd/",
        "   • Comprehensive Windows exploitation training",
        "   • Active Directory, privilege escalation",
        "   • Hands-on lab environments",
        "",
        "⚡ HackTheBox Windows Modules",
        "   • URL: https://academy.hackthebox.com",
        "   • Structured Windows-specific modules",
        "   • Active Directory attack paths",
        "   • Windows service exploitation",
        "",
        "⚡ SANS SEC505",
        "   • URL: https://www.sans.org/cyber-security-training/windows-security/",
        "   • Advanced Windows security techniques",
        "   • Enterprise defense strategies",
        "   • Comprehensive Windows hardening",
        "",
        "【Must-Follow YouTube Channels】",
        "⚡ IppSec",
        "   • https://youtube.com/@IppSec",
        "   • Detailed Windows pentesting walkthroughs",
        "   • CTF and real-world exploitation techniques",
        "",
        "⚡ John Hammond",
        "   • https://youtube.com/@_JohnHammond",
        "   • Windows exploit development",
        "   • Reverse engineering tutorials",
        "",
        "【Essential Reading & Practice】",
        "⚡ PayloadsAllTheThings Windows",
        "   • https://github.com/swisskyrepo/PayloadsAllTheThings/windows-pentesting",
        "   • Comprehensive Windows attack techniques",
        "",
        "【Recommended Learning Path】",
        "1. Foundations",
        "   • Learn PowerShell scripting",
        "   • Understand Windows architecture",
        "   • Master basic Active Directory concepts",
        "",
        "2. Intermediate Skills",
        "   • Practice Active Directory enumeration",
        "   • Learn privilege escalation techniques",
        "   • Study Windows exploit frameworks",
        "",
        "3. Advanced Techniques",
        "   • Master Active Directory attack paths",
        "   • Develop custom exploit techniques",
        "   • Understand advanced persistence methods",
        "",
        "【Essential Tools】",
        "• Metasploit Framework",
        "• PowerSploit",
        "• Mimikatz",
        "• Empire/PowerShell Empire",
        "• Bloodhound",
        "",
        "Reminder: Always practice in controlled environments.",
        "Tip: Build a home lab for safe practice!",
        ">>> TYPE 'BACK' TO RETURN TO THE PREVIOUS PAGE. <<< "};
    size_t numMessages = sizeof(messages) / sizeof(messages[0]);
    for (size_t i = 0; i < numMessages; ++i)
    {
        std::string line = messages[i];
        std::string formatted_msg = PRIVMSG_FORMAT(sender, sender, server_hostname, client.getNickname(), line + "\r\n");
        sendReply(client_fd, formatted_msg);
    }
}
void defaultAnswer(Client &client, int client_fd, std::string server_hostname)
{
    std::string sender = "SECBOT";
    const char *messages[] = {
        "✦ Welcome to SECBOT - Your Security Learning Assistant! ✦",
        "【Available Learning Paths】",
        "",
        "⚡ FOR - Digital Forensics & Incident Response",
        "   Investigate security incidents, perform malware analysis, and master evidence collection",
        "   Skills: Memory forensics, Network forensics, Malware analysis, Chain of custody",
        "",
        "⚡ WEB - Web Application Security",
        "   Learn to identify, exploit, and secure web applications against common threats",
        "   Skills: OWASP Top 10, XSS, SQLi, Authentication bypasses, API security",
        "",
        "⚡ PWN - Binary Exploitation & Reverse Engineering",
        "   Master low-level security, exploit development, and binary analysis",
        "   Skills: Assembly, Buffer overflows, ROP chains, Debuggers, Disassemblers",
        "",
        "⚡ WIN - Windows Systems Penetration Testing",
        "   Active Directory, PowerShell, Windows privileges, Service exploits",
        "",
        "Usage: SECBOT <path>",
        "Examples:",
        "  SECBOT FOR - Shows forensics learning resources and roadmap",
        "  SECBOT WIN - Shows Windows pentesting resources and methodology",
        "",
        "Tip: Each path includes curated resources, practice labs, and recommended certifications.",
        "Type your chosen path to begin your cybersecurity journey!"};
    size_t numMessages = sizeof(messages) / sizeof(messages[0]);
    for (size_t i = 0; i < numMessages; ++i)
    {
        std::string line = messages[i];
        std::string formatted_msg = PRIVMSG_FORMAT(sender, sender, server_hostname, client.getNickname(), line + "\r\n");
        sendReply(client_fd, formatted_msg);
    }
}

void Server::BotCommand(int client_fd, std::vector<std::string> command)
{
    Client &currClient = _clients[client_fd];
    std::string sender = "SECBOT";
    if (command.size() < 2)
    {
        const char *messages[] = {
            "✦ Welcome to SECBOT - Your Security Learning Assistant! ✦",
            "【Available Learning Paths】",
            "",
            "⚡ FOR - Digital Forensics & Incident Response",
            "   Investigate security incidents, perform malware analysis, and master evidence collection",
            "   Skills: Memory forensics, Network forensics, Malware analysis, Chain of custody",
            "",
            "⚡ WEB - Web Application Security",
            "   Learn to identify, exploit, and secure web applications against common threats",
            "   Skills: OWASP Top 10, XSS, SQLi, Authentication bypasses, API security",
            "",
            "⚡ PWN - Binary Exploitation & Reverse Engineering",
            "   Master low-level security, exploit development, and binary analysis",
            "   Skills: Assembly, Buffer overflows, ROP chains, Debuggers, Disassemblers",
            "",
            "⚡ WIN - Windows Systems Penetration Testing",
            "   Active Directory, PowerShell, Windows privileges, Service exploits",
            "",
            "Usage: SECBOT <path>",
            "Examples:",
            "  SECBOT FOR - Shows forensics learning resources and roadmap",
            "  SECBOT WIN - Shows Windows pentesting resources and methodology",
            "",
            "Tip: Each path includes curated resources, practice labs, and recommended certifications.",
            "Type your chosen path to begin your cybersecurity journey!"};

        size_t numMessages = sizeof(messages) / sizeof(messages[0]);
        for (size_t i = 0; i < numMessages; ++i)
        {
            std::string line = messages[i];
            std::string formatted_msg = PRIVMSG_FORMAT(sender, sender, _hostname, currClient.getNickname(), line + "\r\n");
            sendReply(client_fd, formatted_msg);
        }
        return;
    }
    else if (command[1] == "WEB")
        webPath(currClient, client_fd, _hostname);
    else if (command[1] == "FOR")
        forPath(currClient, client_fd, _hostname);
    else if (command[1] == "PWN")
        pwnPath(currClient, client_fd, _hostname);
    else if (command[1] == "WIN")
        windowsPentestPath(currClient, client_fd, _hostname);
    else
        defaultAnswer(currClient, client_fd, _hostname);
}
