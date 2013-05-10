struct table
{
        char tablename[128];
        struct column *firstcolumn;
};
struct column
{
        char col_name[20];
        char type[6];
        int len;
        int isNull;
        struct column *nextcolumn;
        struct data *firstdata;
};
struct data
{
        char *record;
        unsigned int i_ID;
        struct data *nextcolumndata;
		struct data *nextrowdata;
};