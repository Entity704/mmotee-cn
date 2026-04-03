/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_SERVER_REGISTER_H
#define ENGINE_SERVER_REGISTER_H

class CRegister
{
	enum
	{
		REGISTERSTATE_START=0,
		REGISTERSTATE_UPDATE_ADDRS,
		REGISTERSTATE_QUERY_COUNT,
		REGISTERSTATE_HEARTBEAT,
		REGISTERSTATE_REGISTERED,
		REGISTERSTATE_ERROR,
		REGISTERSTATE_DDNET_REGISTER,
		REGISTERSTATE_DDNET_WAIT_CHALLENGE,
		REGISTERSTATE_DDNET_REGISTERED
	};

	struct CMasterserverInfo
	{
		NETADDR m_Addr;
		int m_Count;
		int m_Valid;
		int64 m_LastSend;
	};

	class CNetServer *m_pNetServer;
	class IEngineMasterServer *m_pMasterServer;
	class IConsole *m_pConsole;

	int m_RegisterState;
	int64 m_RegisterStateStart;
	int m_RegisterFirst;
	int m_RegisterCount;

	CMasterserverInfo m_aMasterserverInfo[IMasterServer::MAX_MASTERSERVERS];
	int m_RegisterRegisteredServer;

	// DDNet master server registration state
	char m_aDDNetSecret[64];
	char m_aDDNetChallengeSecret[64];
	char m_aDDNetChallengeToken[64];
	int m_DDNetInfoSerial;
	int64 m_DDNetLastRegister;

	void RegisterNewState(int State);
	void RegisterSendFwcheckresponse(NETADDR *pAddr);
	void RegisterSendHeartbeat(NETADDR Addr);
	void RegisterSendCountRequest(NETADDR Addr);
	void RegisterGotCount(struct CNetChunk *pChunk);

	// ddnet master registration helpers
	bool IsDDNetMaster(int Index) const;
	int DDNetDoRegister(NETADDR Addr);
	void DDNetGotChallenge(const char *pChallengeToken);

public:
	CRegister();
	void Init(class CNetServer *pNetServer, class IEngineMasterServer *pMasterServer, class IConsole *pConsole);
	void RegisterUpdate(int Nettype);
	int RegisterProcessPacket(struct CNetChunk *pPacket);
};

#endif
