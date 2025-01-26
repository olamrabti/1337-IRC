#include "Server.hpp"

void webPath(int client_fd)
{
    sendReply(client_fd,
        "\033[1;31m✦ \033[1;96mSECBOT\033[1;31m Web Application Security Learning Path ✦\033[0m\n\n"
        
        "\033[1;97m【Core Learning Platforms】\033[0m\n"
        "\033[1;32m⚡ PortSwigger Web Security Academy\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://portswigger.net/web-security\033[0m\n"
        "   • Comprehensive, free labs and materials\n"
        "   • Server-side: SQLi, XXE, SSRF, Path Traversal\n"
        "   • Client-side: XSS, CSRF, CORS, Clickjacking\n"
        "   • Advanced: JWT, OAuth, GraphQL, Prototype Pollution\n\n"

        "\033[1;32m⚡ HackTheBox Academy\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://academy.hackthebox.com\033[0m\n"
        "   • Structured modules with hands-on labs\n"
        "   • Web fundamentals to advanced exploitation\n"

        "\033[1;32m⚡ PentesterLab\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://pentesterlab.com\033[0m\n"
        "   • Progressive learning badges\n"
        "   • Essentials → Unix → PCAP → White Badge\n"
        "   • Real-world vulnerability scenarios\n\n"

        "\033[1;97m【Must-Follow YouTube Channels】\033[0m\n"
        "\033[1;32m⚡ PwnFunction\033[0m\n"
        "   • \033[4mhttps://youtube.com/@PwnFunction\033[0m\n"
        "   • Animated vulnerability explanations\n"
        "   • Clear, concise technical breakdowns\n\n"

        "\033[1;32m⚡ Bug Bounty Reports Explained\033[0m\n"
        "   • \033[4mhttps://youtube.com/@BugBountyReportsExplained\033[0m\n"
        "   • Real-world vulnerability analysis\n"
        "   • Detailed methodology explanations\n\n"

        "\033[1;32m⚡ STÖK & NahamSec\033[0m\n"
        "   • \033[4mhttps://youtube.com/@STOKfredrik\033[0m\n"
        "   • \033[4mhttps://youtube.com/@NahamSec\033[0m\n"
        "   • Bug bounty methodology\n"
        "   • Live hacking & tool tutorials\n\n"

        "\033[1;97m【Essential Reading & Practice】\033[0m\n"
        "\033[1;32m⚡ Pentester Land Write-ups\033[0m\n"
        "   • \033[4mhttps://pentester.land/writeups\033[0m\n"
        "   • Bug bounty methodology & reports\n\n"

        "\033[1;32m⚡ PortSwigger Daily Swig\033[0m\n"
        "   • \033[4mhttps://portswigger.net/daily-swig\033[0m\n"
        "   • Latest web security news & research\n\n"

        "\033[1;32m⚡ Orange's Blog & Challenges\033[0m\n"
        "   • Blog: \033[4mhttps://blog.orange.tw\033[0m\n"
        "   • CTF: \033[4mhttps://github.com/orangetw/My-CTF-Web-Challenges\033[0m\n"
        "   • Advanced exploitation techniques\n\n"

        "\033[1;32m⚡ PicoCTF\033[0m\n"
        "   • \033[4mhttps://picoctf.org\033[0m\n"
        "   • Perfect for beginners\n"
        "   • Progressive difficulty challenges\n\n"

        "\033[1;32m⚡ Beginner's Bug Bounty Guide\033[0m\n"
        "   • \033[4mhttps://blog.securitybreached.org/2023/08/18/bug-bounty-blueprint-a-beginners-guide\033[0m\n"
        "   • Complete methodology & tools guide\n\n"

        "\033[1;97m【Recommended Learning Path】\033[0m\n"
        "\033[1;93m1. Foundations \033[0m\n"
        "   • Complete PortSwigger Academy fundamentals\n"
        "   • Solve PicoCTF web challenges\n"
        "   • Watch PwnFunction videos\n\n"

        "\033[1;93m2. Building Skills \033[0m\n"
        "   • Follow PentesterLab badge progression\n"
        "   • Start HackTheBox Academy modules\n"
        "   • Practice on beginner bug bounty programs\n\n"

        "\033[1;93m3. Advanced Topics \033[0m\n"
        "   • Tackle Orange's CTF challenges\n"
        "   • Study bug bounty write-ups\n"
        "   • Follow security news and research\n\n"

        "\033[1;97m【Essential Tools】\033[0m\n"
        "• Burp Suite Community/Pro\n"
        "• Firefox + Developer Tools\n"
        "• OWASP ZAP\n"
        "• Dirsearch/Gobuster\n"
        "• Nuclei\n\n"

        "\033[1;31mReminder:\033[0m Always follow platform rules and practice ethically.\n"
        "\033[1;36mTip:\033[0m Take detailed notes and document your learning journey!\n");
}

void forPath(int client_fd)
{
    sendReply(client_fd,
        "\033[1;31m✦ \033[1;96mSECBOT\033[1;31m Digital Forensics & Incident Response Path ✦\033[0m\n\n"
        
        "\033[1;97m【Core Learning Platforms】\033[0m\n"
        "\033[1;32m⚡ SANS Digital Forensics\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://www.sans.org/cyber-security-courses/digital-forensics-essentials\033[0m\n"
        "   • Industry standard training\n"
        "   • Hands-on forensics investigation\n"
        "   • Incident response procedures\n\n"

        "\033[1;32m⚡ TCM Security - Practical Windows Forensics\033[0m\n"
        "   • \033[4mhttps://academy.tcm-sec.com/p/practical-windows-forensics\033[0m\n"
        "   • Windows artifacts analysis\n"
        "   • Memory forensics\n"
        "   • Evidence acquisition\n\n"

        "\033[1;32m⚡ 13Cubed Videos\033[0m\n"
        "   • \033[4mhttps://youtube.com/@13cubed\033[0m\n"
        "   • Detailed forensics tutorials\n"
        "   • Tool demonstrations\n"
        "   • Real case analysis\n\n"

        "\033[1;97m【Essential Tools & Resources】\033[0m\n"
        "\033[1;32m⚡ Memory Forensics - Volatility\033[0m\n"
        "   • \033[4mhttps://volatilityfoundation.org\033[0m\n"
        "   • Memory analysis framework\n"
        "   • Process analysis\n"
        "   • Malware detection\n\n"

        "\033[1;32m⚡ Disk Forensics\033[0m\n"
        "   • FTK Imager: \033[4mhttps://accessdata.com/product-download/ftk-imager-version-4-5\033[0m\n"
        "   • Autopsy: \033[4mhttps://autopsy.com/download\033[0m\n"
        "   • The Sleuth Kit: \033[4mhttps://sleuthkit.org\033[0m\n\n"

        "\033[1;32m⚡ Network Forensics\033[0m\n"
        "   • Wireshark: \033[4mhttps://wireshark.org\033[0m\n"
        "   • NetworkMiner: \033[4mhttps://netresec.com/?page=NetworkMiner\033[0m\n"
        "   • Zeek: \033[4mhttps://zeek.org\033[0m\n\n"

        "\033[1;97m【Practice Platforms】\033[0m\n"
        "\033[1;32m⚡ Digital Forensics CTFs\033[0m\n"
        "   • Digital Forensics CTF: \033[4mhttps://dfir.training\033[0m\n"
        "   • Forensics CTF Challenges: \033[4mhttps://github.com/frankito-test/forensics-ctf\033[0m\n\n"

        "\033[1;32m⚡ HackTheBox Forensics Challenges\033[0m\n"
        "   • \033[4mhttps://app.hackthebox.com/challenges/forensics\033[0m\n\n"

        "\033[1;97m【Key Learning Resources】\033[0m\n"
        "\033[1;32m⚡ DFIR Community Blog\033[0m\n"
        "   • \033[4mhttps://aboutdfir.com\033[0m\n"
        "   • Case studies\n"
        "   • Tool tutorials\n"
        "   • Investigation techniques\n\n"

        "\033[1;32m⚡ SANS DFIR Blog\033[0m\n"
        "   • \033[4mhttps://www.sans.org/blog/digital-forensics\033[0m\n"
        "   • Expert articles\n"
        "   • Research papers\n\n"

        "\033[1;97m【Recommended Learning Path】\033[0m\n"
        "\033[1;93m1. Foundations \033[0m\n"
        "   • Basic system architecture\n"
        "   • File systems and data structures\n"
        "   • Digital evidence handling\n"
        "   • Basic tool familiarity\n\n"

        "\033[1;93m2. Core Skills \033[0m\n"
        "   • Memory analysis with Volatility\n"
        "   • Disk forensics with Autopsy/FTK\n"
        "   • Network packet analysis\n"
        "   • Windows/Linux artifacts\n\n"

        "\033[1;93m3. Advanced Topics \033[0m\n"
        "   • Malware analysis\n"
        "   • Mobile device forensics\n"
        "   • Cloud forensics\n"
        "   • Anti-forensics techniques\n\n"

        "\033[1;97m【Certifications Path】\033[0m\n"
        "• SANS GCFE (GIAC Certified Forensic Examiner)\n"
        "• EnCase Certified Examiner (EnCE)\n"
        "• AccessData Certified Examiner (ACE)\n"
        "• Certified Computer Forensics Examiner (CCFE)\n\n"

        "\033[1;97m【Essential Investigation Areas】\033[0m\n"
        "• Windows Registry Analysis\n"
        "• Browser Forensics\n"
        "• Email Investigation\n"
        "• Memory Analysis\n"
        "• Timeline Analysis\n"
        "• Log File Analysis\n\n"

        "\033[1;36mTip:\033[0m Build your own forensics lab for practice!\n"
        "\033[1;31mReminder:\033[0m Always maintain proper chain of custody in real investigations.\n");
}

void pwnPath(int client_fd)
{
    sendReply(client_fd,
        "\033[1;31m✦ \033[1;96mSECBOT\033[1;31m Binary Exploitation & Reverse Engineering Path ✦\033[0m\n\n"
        
        "\033[1;97m【Core Learning Resources】\033[0m\n"
        "\033[1;32m⚡ Guyinatuxedo's Pwn Guide\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://guyinatuxedo.github.io\033[0m\n"
        "   • Comprehensive binary exploitation tutorials\n"
        "   • Hands-on exploit development\n"
        "   • Assembly and low-level programming\n\n"

        "\033[1;32m⚡ LiveOverflow\033[0m\n"
        "   • \033[4mhttps://youtube.com/@LiveOverflow\033[0m\n"
        "   • Binary exploitation video series\n"
        "   • CTF challenge walkthroughs\n"
        "   • Deep technical explanations\n\n"

        "\033[1;32m⚡ The Nightmare Exploitation Course\033[0m\n"
        "   • \033[4mhttps://guyinatuxedo.github.io/intro.html\033[0m\n"
        "   • Step-by-step pwn challenges\n"
        "   • Progressive difficulty\n"
        "   • Covers multiple exploitation techniques\n\n"

        "\033[1;97m【Practice Platforms】\033[0m\n"
        "\033[1;32m⚡ PWN Challenge Sites\033[0m\n"
        "   • PicoCTF: \033[4mhttps://picoctf.org\033[0m\n"
        "   • HackTheBox: \033[4mhttps://app.hackthebox.com/challenges/pwn\033[0m\n"
        "   • ROP Emporium: \033[4mhttp://ropemporium.com\033[0m\n\n"

        "\033[1;97m【Essential Tools】\033[0m\n"
        "\033[1;32m⚡ Reverse Engineering\033[0m\n"
        "   • Ghidra: \033[4mhttps://ghidra-sre.org\033[0m\n"
        "   • IDA Pro\n"
        "   • Binary Ninja\n"
        "   • Radare2\n\n"

        "\033[1;32m⚡ Exploitation Tools\033[0m\n"
        "   • GDB (GNU Debugger)\n"
        "   • Pwntools\n"
        "   • ROPgadget\n"
        "   • Checksec\n\n"

        "\033[1;97m【Learning Path】\033[0m\n"
        "\033[1;93m1. Foundations \033[0m\n"
        "   • Assembly language basics\n"
        "   • Memory layout & stack concepts\n"
        "   • Basic buffer overflows\n"
        "   • Linux environment setup\n\n"

        "\033[1;93m2. Intermediate Skills \033[0m\n"
        "   • ROP (Return Oriented Programming)\n"
        "   • GOT/PLT hijacking\n"
        "   • Format string vulnerabilities\n"
        "   • Shellcode development\n\n"

        "\033[1;93m3. Advanced Techniques \033[0m\n"
        "   • Heap exploitation\n"
        "   • Advanced ROP techniques\n"
        "   • Kernel exploitation\n"
        "   • Advanced anti-debugging\n\n"

        "\033[1;97m【Key YouTube Channels】\033[0m\n"
        "• LiveOverflow\n"
        "• 0x41414141\n"
        "• John Hammond\n"
        "• VulnHub\n\n"

        "\033[1;97m【Recommended Books】\033[0m\n"
        "• The Shellcoder's Handbook\n"
        "• Practical Malware Analysis\n"
        "• Hacking: The Art of Exploitation\n\n"

        "\033[1;36mTip:\033[0m Build a dedicated Linux VM for practice!\n"
        "\033[1;31mReminder:\033[0m Always practice ethically and legally.\n");
}

void windowsPentestPath(int client_fd)
{
    sendReply(client_fd,
        "\033[1;31m✦ \033[1;96mSECBOT\033[1;31m Windows Penetration Testing Learning Path ✦\033[0m\n\n"
        
        "\033[1;97m【Core Learning Platforms】\033[0m\n"
        "\033[1;32m⚡ Offensive Security WinEXP\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://www.offensive-security.com/winexd/\033[0m\n"
        "   • Comprehensive Windows exploitation training\n"
        "   • Active Directory, privilege escalation\n"
        "   • Hands-on lab environments\n\n"

        "\033[1;32m⚡ HackTheBox Windows Modules\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://academy.hackthebox.com\033[0m\n"
        "   • Structured Windows-specific modules\n"
        "   • Active Directory attack paths\n"
        "   • Windows service exploitation\n\n"

        "\033[1;32m⚡ SANS SEC505\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://www.sans.org/cyber-security-training/windows-security/\033[0m\n"
        "   • Advanced Windows security techniques\n"
        "   • Enterprise defense strategies\n"
        "   • Comprehensive Windows hardening\n\n"

        "\033[1;97m【Must-Follow YouTube Channels】\033[0m\n"
        "\033[1;32m⚡ IppSec\033[0m\n"
        "   • \033[4mhttps://youtube.com/@IppSec\033[0m\n"
        "   • Detailed Windows pentesting walkthroughs\n"
        "   • CTF and real-world exploitation techniques\n\n"

        "\033[1;32m⚡ John Hammond\033[0m\n"
        "   • \033[4mhttps://youtube.com/@_JohnHammond\033[0m\n"
        "   • Windows exploit development\n"
        "   • Reverse engineering tutorials\n\n"

        "\033[1;97m【Essential Reading & Practice】\033[0m\n"
        "\033[1;32m⚡ PayloadsAllTheThings Windows\033[0m\n"
        "   • \033[4mhttps://github.com/swisskyrepo/PayloadsAllTheThings/windows-pentesting\033[0m\n"
        "   • Comprehensive Windows attack techniques\n\n"

        "\033[1;97m【Recommended Learning Path】\033[0m\n"
        "\033[1;93m1. Foundations \033[0m\n"
        "   • Learn PowerShell scripting\n"
        "   • Understand Windows architecture\n"
        "   • Master basic Active Directory concepts\n\n"

        "\033[1;93m2. Intermediate Skills \033[0m\n"
        "   • Practice Active Directory enumeration\n"
        "   • Learn privilege escalation techniques\n"
        "   • Study Windows exploit frameworks\n\n"

        "\033[1;93m3. Advanced Techniques \033[0m\n"
        "   • Master Active Directory attack paths\n"
        "   • Develop custom exploit techniques\n"
        "   • Understand advanced persistence methods\n\n"

        "\033[1;97m【Essential Tools】\033[0m\n"
        "• Metasploit Framework\n"
        "• PowerSploit\n"
        "• Mimikatz\n"
        "• Empire/PowerShell Empire\n"
        "• Bloodhound\n\n"

        "\033[1;31mReminder:\033[0m Always practice in controlled environments.\n"
        "\033[1;36mTip:\033[0m Build a home lab for safe practice!\n");
}

void linuxPentestPath(int client_fd)
{
    sendReply(client_fd,
        "\033[1;31m✦ \033[1;96mSECBOT\033[1;31m Linux Penetration Testing Learning Path ✦\033[0m\n\n"
        
        "\033[1;97m【Core Learning Platforms】\033[0m\n"
        "\033[1;32m⚡ Offensive Security PWK/OSCP\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://www.offsec.com/courses/pen-200/\033[0m\n"
        "   • Gold standard Linux/Unix pentesting certification\n"
        "   • Comprehensive Linux exploitation techniques\n"
        "   • Hands-on lab environment\n\n"

        "\033[1;32m⚡ HackTheBox Academy\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://academy.hackthebox.com\033[0m\n"
        "   • Structured Linux pentesting modules\n"
        "   • Network and system exploitation\n"
        "   • Advanced Linux attack techniques\n\n"

        "\033[1;32m⚡ VulnHub\033[0m\n"
        "   • \033[1;93mURL:\033[0m \033[4mhttps://www.vulnhub.com/\033[0m\n"
        "   • Free vulnerable Linux machines\n"
        "   • Practical hands-on experience\n"
        "   • Wide range of difficulty levels\n\n"

        "\033[1;97m【Must-Follow YouTube Channels】\033[0m\n"
        "\033[1;32m⚡ NetworkChuck\033[0m\n"
        "   • \033[4mhttps://youtube.com/@NetworkChuck\033[0m\n"
        "   • Linux security and networking\n"
        "   • Practical hacking demonstrations\n\n"

        "\033[1;32m⚡ George Karagkiaouris\033[0m\n"
        "   • \033[4mhttps://youtube.com/@GeorgeKaragkiaouris\033[0m\n"
        "   • In-depth Linux pentesting tutorials\n"
        "   • Detailed exploit walkthroughs\n\n"

        "\033[1;97m【Essential Reading & Practice】\033[0m\n"
        "\033[1;32m⚡ PayloadsAllTheThings Linux\033[0m\n"
        "   • \033[4mhttps://github.com/swisskyrepo/PayloadsAllTheThings/linux-pentesting\033[0m\n"
        "   • Comprehensive Linux attack techniques\n\n"

        "\033[1;97m【Recommended Learning Path】\033[0m\n"
        "\033[1;93m1. Foundations \033[0m\n"
        "   • Master Linux command-line\n"
        "   • Learn Bash scripting\n"
        "   • Understand Linux system architecture\n\n"

        "\033[1;93m2. Intermediate Skills \033[0m\n"
        "   • Practice privilege escalation\n"
        "   • Study network reconnaissance\n"
        "   • Learn exploit development\n\n"

        "\033[1;93m3. Advanced Techniques \033[0m\n"
        "   • Master kernel exploitation\n"
        "   • Develop custom exploit chains\n"
        "   • Advanced persistence methods\n\n"

        "\033[1;97m【Essential Tools】\033[0m\n"
        "• Metasploit Framework\n"
        "• Nmap\n"
        "• Wireshark\n"
        "• Burp Suite\n"
        "• Gobuster\n\n"

        "\033[1;36mTip:\033[0m Build a home lab for safe practice!\n");
}

void Server::BotCommand(int client_fd, std::vector<std::string> command)
{
    Client &currClient = _clients[client_fd];
    std::cout << "SECBOT set for client " << currClient.getNickname() << std::endl;
    if (command.size() < 2)
    {
        sendReply(client_fd, 
            "\033[1;31m✦ Welcome to \033[1;96mSECBOT\033[1;31m - Your Security Learning Assistant! ✦\033[0m\n\n"
            "\033[1;97m【Available Learning Paths】\033[0m\n"
            "\033[1;32m⚡ FOR\033[0m - \033[1;93mDigital Forensics & Incident Response\033[0m\n"
            "     Investigate security incidents, perform malware analysis, and master evidence collection\n"
            "     Skills: Memory forensics, Network forensics, Malware analysis, Chain of custody\n\n"
            
            "\033[1;32m⚡ WEB\033[0m - \033[1;93mWeb Application Security\033[0m\n"
            "     Learn to identify, exploit, and secure web applications against common threats\n"
            "     Skills: OWASP Top 10, XSS, SQLi, Authentication bypasses, API security\n\n"
            
            "\033[1;32m⚡ PWN\033[0m - \033[1;93mBinary Exploitation & Reverse Engineering\033[0m\n"
            "     Master low-level security, exploit development, and binary analysis\n"
            "     Skills: Assembly, Buffer overflows, ROP chains, Debuggers, Disassemblers\n\n"
            
            "\033[1;32m⚡ PEN\033[0m - \033[1;93mPenetration Testing\033[0m\n"
            "     Professional ethical hacking and security assessment techniques\n"
            "     Choose your specialization:\n"
            "     \033[1;34m└─►\033[0m \033[1;95mWIN\033[0m - Windows Systems\n"
            "          Active Directory, PowerShell, Windows privileges, Service exploits\n"
            "     \033[1;34m└─►\033[0m \033[1;95mLIN\033[0m - Linux Systems\n"
            "          Privilege escalation, Service enumeration, Bash scripting, Kernel exploits\n\n"
            
            "\033[1;36mUsage:\033[0m SECBOT <path>\n"
            "\033[1;97mExamples:\033[0m\n"
            "  \033[1;32mSECBOT FOR\033[0m - Shows forensics learning resources and roadmap\n"
            "  \033[1;32mSECBOT PEN WIN\033[0m - Shows Windows pentesting resources and methodology\n\n"
            
            "\033[1;93mTip:\033[0m Each path includes curated resources, practice labs, and recommended certifications.\n"
            "Type your chosen path to begin your cybersecurity journey!\n");
        return;
    }
    else if (command[1] == "WEB")
        webPath(client_fd);
    else if (command[1] == "FOR")
        forPath(client_fd);
    else if (command[1] == "PWN")
        pwnPath(client_fd);
    else if (command[1] == "PEN")
    {
        if (command.size() < 3)
        sendReply(client_fd,  "     Choose your specialization:\n"
            "     \033[1;34m└─►\033[0m \033[1;95mWIN\033[0m - Windows Systems\n"
            "          Active Directory, PowerShell, Windows privileges, Service exploits\n"
            "     \033[1;34m└─►\033[0m \033[1;95mLIN\033[0m - Linux Systems\n"
            "          Privilege escalation, Service enumeration, Bash scripting, Kernel exploits\n\n");
        else if (command[2] == "WIN")
            windowsPentestPath(client_fd);
        else if (command[2] == "LIN")
            linuxPentestPath(client_fd);
    }
}
