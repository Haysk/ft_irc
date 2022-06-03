void irc_core_init(void); void irc_core_deinit(void);
void irc_dcc_init(void);void irc_flood_init(void);void irc_notifylist_init(void);
void irc_notifylist_deinit(void);void irc_flood_deinit(void);void irc_dcc_deinit(void);
void irc_init(void) { irc_core_init();  irc_dcc_init(); irc_flood_init(); irc_notifylist_init(); }
void irc_deinit(void) { irc_notifylist_deinit(); irc_flood_deinit(); irc_dcc_deinit();  irc_core_deinit(); }
