#include "Server.hpp"

void Server::BotCommand(int client_fd, std::vector<std::string> command)
{
    Client &currClient = _clients[client_fd];
    std::cout << "SECBOT set for client " << currClient.getNickname() << std::endl;
    if (command.size() < 2)
    {
        sendReply(client_fd, 
            "\033[1;31m✦ Welcome to \033[1;96mSECBOT\033[1;31m - Your Security Learning Assistant! ✦\033[0m\n\n"
            "\033[1;97m【Available Learning Paths】\033[0m\n"
            "\033[1;32m⚡ FOR\033[0m - \033[1;93mDigital Forensics\033[0m & Incident Response\n"
            "     Investigate security incidents, perform malware analysis, and master evidence collection\n"
            "     Skills: Memory forensics, Network forensics, Malware analysis, Chain of custody\n\n"
            
            "\033[1;32m⚡ WEB\033[0m - \033[1;93mWeb Application Security\033[0m\n"
            "     Learn to identify, exploit, and secure web applications against common threats\n"
            "     Skills: OWASP Top 10, XSS, SQLi, Authentication bypasses, API security\n\n"
            
            "\033[1;32m⚡ CRY\033[0m - \033[1;93mCryptography\033[0m & Encryption\n"
            "     Understand modern cryptography, encryption algorithms, and their implementations\n"
            "     Skills: Symmetric/Asymmetric encryption, Hashing, PKI, Crypto attacks\n\n"
            
            "\033[1;32m⚡ PWN\033[0m - \033[1;93mBinary Exploitation\033[0m & Reverse Engineering\n"
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
}