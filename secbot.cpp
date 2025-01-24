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
            
            "\033[1;32m⚡ SOC\033[0m - \033[1;93mSecurity Operations Center\033[0m\n"
            "     Learn to monitor, detect, and respond to security threats in real-time\n"
            "     Skills: SIEM, Threat hunting, Log analysis, Incident response, Network monitoring\n\n"
            
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
}