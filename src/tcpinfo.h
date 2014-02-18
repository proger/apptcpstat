/*
 * xnu-2422.1.72
 */

#pragma pack(4)

struct tcp_info {
	uint8_t	tcpi_state;			/* TCP FSM state. */
	uint8_t	tcpi_options;		/* Options enabled on conn. */
	uint8_t	tcpi_snd_wscale;	/* RFC1323 send shift value. */
	uint8_t	tcpi_rcv_wscale;	/* RFC1323 recv shift value. */

	uint32_t	tcpi_flags;			/* extra flags (TCPI_FLAG_xxx) */

	uint32_t	tcpi_rto;			/* Retransmission timeout in milliseconds */
	uint32_t	tcpi_snd_mss;		/* Max segment size for send. */
	uint32_t	tcpi_rcv_mss;		/* Max segment size for receive. */

	uint32_t	tcpi_rttcur;		/* Most recent value of RTT */
	uint32_t	tcpi_srtt;			/* Smoothed RTT */
	uint32_t	tcpi_rttvar;		/* RTT variance */
	uint32_t	tcpi_rttbest;		/* Best RTT we've seen */

	uint32_t	tcpi_snd_ssthresh;	/* Slow start threshold. */
	uint32_t	tcpi_snd_cwnd;		/* Send congestion window. */

	uint32_t	tcpi_rcv_space;		/* Advertised recv window. */

	uint32_t	tcpi_snd_wnd;		/* Advertised send window. */
	uint32_t	tcpi_snd_nxt;		/* Next egress seqno */
	uint32_t	tcpi_rcv_nxt;		/* Next ingress seqno */
	
	int32_t		tcpi_last_outif;	/* if_index of interface used to send last */
	uint32_t	tcpi_snd_sbbytes;	/* bytes in snd buffer including data inflight */
	
	uint64_t	tcpi_txpackets __attribute__((aligned(8)));	/* total packets sent */
	uint64_t	tcpi_txbytes __attribute__((aligned(8)));
									/* total bytes sent */	
	uint64_t	tcpi_txretransmitbytes __attribute__((aligned(8)));
									/* total bytes retransmitted */	
	uint64_t	tcpi_txunacked __attribute__((aligned(8)));
									/* current number of bytes not acknowledged */	
	uint64_t	tcpi_rxpackets __attribute__((aligned(8)));	/* total packets received */
	uint64_t	tcpi_rxbytes __attribute__((aligned(8)));
									/* total bytes received */
	uint64_t	tcpi_rxduplicatebytes __attribute__((aligned(8)));
									/* total duplicate bytes received */
	uint64_t	tcpi_rxoutoforderbytes __attribute__((aligned(8)));
									/* total out of order bytes received */
	uint64_t	tcpi_snd_bw __attribute__((aligned(8)));	/* measured send bandwidth in bits/sec */
	uint8_t	tcpi_synrexmits;	/* Number of syn retransmits before connect */
	uint8_t	tcpi_unused1;
	uint16_t	tcpi_unused2;
	uint64_t	tcpi_cell_rxpackets __attribute((aligned(8)));	/* packets received over cellular */
	uint64_t	tcpi_cell_rxbytes __attribute((aligned(8)));	/* bytes received over cellular */
	uint64_t	tcpi_cell_txpackets __attribute((aligned(8)));	/* packets transmitted over cellular */
	uint64_t	tcpi_cell_txbytes __attribute((aligned(8)));	/* bytes transmitted over cellular */
	uint64_t	tcpi_wifi_rxpackets __attribute((aligned(8)));	/* packets received over Wi-Fi */
	uint64_t	tcpi_wifi_rxbytes __attribute((aligned(8)));	/* bytes received over Wi-Fi */
	uint64_t	tcpi_wifi_txpackets __attribute((aligned(8)));	/* packets transmitted over Wi-Fi */
	uint64_t	tcpi_wifi_txbytes __attribute((aligned(8)));	/* bytes transmitted over Wi-Fi */
};
#pragma pack()

char *tcp_info_str(struct tcp_info *info);

int ats_tcpinfo(int fd, struct tcp_info *info);
