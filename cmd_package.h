struct Command {
   char type;
   unsigned long int to;
   unsigned long int who;
   unsigned long int cmd1;
   unsigned long int cmd1_param[2];
   unsigned long int cmd2;
   unsigned long int cmd2_param[2];
   unsigned long int cmd3;
   unsigned long int cmd3_param[2];
   char execute;
};
