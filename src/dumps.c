#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include "tcpinfo.h"

char *
tcp_info_str(struct tcp_info *var)
{
	char *buf = NULL;
	asprintf(&buf,
		"    tcpi_state = %hhu\n"
		"    tcpi_options = %hhu\n"
		"    tcpi_snd_wscale = %hhu\n"
		"    tcpi_rcv_wscale = %hhu\n"
		"    tcpi_flags = %lu\n"
		"    tcpi_rto = %lu\n"
		"    tcpi_snd_mss = %lu\n"
		"    tcpi_rcv_mss = %lu\n"
		"    tcpi_rttcur = %lu\n"
		"    tcpi_srtt = %lu\n"
		"    tcpi_rttvar = %lu\n"
		"    tcpi_rttbest = %lu\n"
		"    tcpi_snd_ssthresh = %lu\n"
		"    tcpi_snd_cwnd = %lu\n"
		"    tcpi_rcv_space = %lu\n"
		"    tcpi_snd_wnd = %lu\n"
		"    tcpi_snd_nxt = %lu\n"
		"    tcpi_rcv_nxt = %lu\n"
		"    tcpi_last_outif = %ld\n"
		"    tcpi_snd_sbbytes = %lu\n"
		"    tcpi_txpackets = %llu\n"
		"    tcpi_txbytes = %llu\n"
		"    tcpi_txretransmitbytes = %llu\n"
		"    tcpi_txunacked = %llu\n"
		"    tcpi_rxpackets = %llu\n"
		"    tcpi_rxbytes = %llu\n"
		"    tcpi_rxduplicatebytes = %llu\n"
		"    tcpi_rxoutoforderbytes = %llu\n"
		"    tcpi_snd_bw = %llu\n"
		"    tcpi_synrexmits = %hhu\n"
		"    tcpi_unused1 = %hhu\n"
		"    tcpi_unused2 = %hu\n"
		"    tcpi_cell_rxpackets = %llu\n"
		"    tcpi_cell_rxbytes = %llu\n"
		"    tcpi_cell_txpackets = %llu\n"
		"    tcpi_cell_txbytes = %llu\n"
		"    tcpi_wifi_rxpackets = %llu\n"
		"    tcpi_wifi_rxbytes = %llu\n"
		"    tcpi_wifi_txpackets = %llu\n"
		"    tcpi_wifi_txbytes = %llu",
		var->tcpi_state,
		var->tcpi_options,
		var->tcpi_snd_wscale,
		var->tcpi_rcv_wscale,
		var->tcpi_flags,
		var->tcpi_rto,
		var->tcpi_snd_mss,
		var->tcpi_rcv_mss,
		var->tcpi_rttcur,
		var->tcpi_srtt,
		var->tcpi_rttvar,
		var->tcpi_rttbest,
		var->tcpi_snd_ssthresh,
		var->tcpi_snd_cwnd,
		var->tcpi_rcv_space,
		var->tcpi_snd_wnd,
		var->tcpi_snd_nxt,
		var->tcpi_rcv_nxt,
		var->tcpi_last_outif,
		var->tcpi_snd_sbbytes,
		var->tcpi_txpackets,
		var->tcpi_txbytes,
		var->tcpi_txretransmitbytes,
		var->tcpi_txunacked,
		var->tcpi_rxpackets,
		var->tcpi_rxbytes,
		var->tcpi_rxduplicatebytes,
		var->tcpi_rxoutoforderbytes,
		var->tcpi_snd_bw,
		var->tcpi_synrexmits,
		var->tcpi_unused1,
		var->tcpi_unused2,
		var->tcpi_cell_rxpackets,
		var->tcpi_cell_rxbytes,
		var->tcpi_cell_txpackets,
		var->tcpi_cell_txbytes,
		var->tcpi_wifi_rxpackets,
		var->tcpi_wifi_rxbytes,
		var->tcpi_wifi_txpackets,
		var->tcpi_wifi_txbytes);
	return buf;
}

