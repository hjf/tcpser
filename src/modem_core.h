#ifndef MODEM_CORE_H
#define MODEM_CORE_H 1

typedef enum {
  MDM_RESP_OK =             0,  // Common code
  MDM_RESP_CONNECT =        1,  // Common code
  MDM_RESP_RING =           2,  // Common code
  MDM_RESP_NO_CARRIER =     3,  // Common code
  MDM_RESP_ERROR =          4,  // Common code
  MDM_RESP_CONNECT_1200 =   5,  // Common code
  MDM_RESP_NO_DIALTONE =    6,  // Common code
  MDM_RESP_BUSY =           7,  // Common code
  MDM_RESP_NO_ANSWER =      8,  // Common code
  MDM_RESP_CONNECT_0600 =   9,  // Conexant code
  MDM_RESP_CONNECT_2400 =   10, // Common code
  MDM_RESP_CONNECT_4800 =   11, // Common code
  MDM_RESP_CONNECT_9600 =   12, // Common code
  MDM_RESP_CONNECT_14400 =  13, // Hayes code
  MDM_RESP_CONNECT_19200 =  14, // Hayes code
  MDM_RESP_CONNECT_57600 =  18, // Conexant code
  MDM_RESP_CONNECT_115200 = 19, // Conexant code
  MDM_RESP_CONNECT_230400 = 20, // Conexant code
  MDM_RESP_CONNECT_460800 = 21, // Conexant code
  MDM_RESP_CONNECT_921600 = 22, // Conexant code
  MDM_RESP_CONNECT_7200 =   24, // Hayes code
  MDM_RESP_CONNECT_12000 =  25, // Hayes code
  MDM_RESP_CONNECT_38400 =  28, // Hayes code
  MDM_RESP_END_OF_LIST
} modem_response;

#define MDM_FC_RTS 1
#define MDM_FC_XON 2

typedef enum {
  MDM_CONN_NONE = 0,
  MDM_CONN_OUTGOING = 1,
  MDM_CONN_INCOMING = 2
} conn_type;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#include "dce.h"
#include "line.h"
#include "nvt.h"

typedef struct x_config {
} x_config;

enum {
  S_REG_RINGS = 0,
  S_REG_RING_COUNT = 1,
  S_REG_BREAK = 2,
  S_REG_CR = 3,
  S_REG_LF = 4,
  S_REG_BS = 5,
  S_REG_BLIND_WAIT = 6,
  S_REG_CARRIER_WAIT = 7,
  S_REG_COMMA_PAUSE = 8,
  S_REG_CARRIER_TIME = 9,
  S_REG_CARRIER_LOSS = 10,
  S_REG_DTMF_TIME = 11,
  S_REG_GUARD_TIME = 12,
  S_REG_INACTIVITY_TIME = 30,
  S_REG_MAX_ARRAY_SIZE
};

typedef struct modem_config {
  // master configuration information
  int mp[2][2];
  int cp[2][2];
  int wp[2][2];
  char no_answer[256];
  char local_connect[256];
  char remote_connect[256];
  char local_answer[256];
  char remote_answer[256];
  char inactive[256];
  int direct_conn;
  char direct_conn_num[256];

  // need to eventually change these
  dce_config dce_data;
  line_config line_data;
  int line_speed;
  int conn_type;
  int is_ringing;
  int is_off_hook;
  int dsr_active;
  int force_dsr;
  int force_dcd;
  int invert_dsr;
  int invert_dcd;
  int allow_transmit;
  int is_binary_negotiated;
  int ring_ctr;
  // command information
  int pre_break_delay;
  unsigned char first_ch;
  int is_cmd_started;
  int is_cmd_mode;
  char cur_line[1024];
  int cur_line_idx;
  int last_line_idx;
  // dailing information
  char dialno[256];
  char last_dialno[256];
  char dial_type;
  char last_dial_type;
  int memory_dial;
  // modem config
  int connect_response;
  int response_code_level;
  int send_responses;
  int text_responses;
  int is_echo;
  int s[S_REG_MAX_ARRAY_SIZE];
  int break_len;
  int disconnect_delay;
  char crlf[3];
  int enable_callerid;
  int is_callerid;
} modem_config;

void mdm_init(void);
void mdm_init_config(modem_config *cfg);
int mdm_set_control_lines(modem_config *cfg);
void mdm_write_char(modem_config *cfg, unsigned char data);
void mdm_write(modem_config *cfg, unsigned char *data, int len);
void mdm_send_response(int msg, modem_config *cfg);
int mdm_off_hook(modem_config *cfg);
int mdm_answer(modem_config *cfg);
int mdm_print_speed(modem_config *cfg);
int mdm_connect(modem_config *cfg);
int mdm_listen(modem_config *cfg);
int mdm_disconnect(modem_config *cfg, unsigned char force);
int mdm_parse_cmd(modem_config *cfg);
int mdm_handle_char(modem_config *cfg, unsigned char ch);
int mdm_clear_break(modem_config *cfg);
int mdm_parse_data(modem_config *cfg, unsigned char *data, int len);
int mdm_handle_timeout(modem_config *cfg);
int mdm_send_ring(modem_config *cfg);
int mdm_read(modem_config *cfg, unsigned char *data, int len);

#include "line.h"
#include "dce.h"

#endif
