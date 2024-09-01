//#define _CRT_SECURE_NO_WARNINGS 

typedef enum {
	eShowAll, eShowComp, eShowU, eShowEmp, eShowBank, eAddComp, eAddPack, eAddUser, eAddEmp, eAddArea,
	eSortU, eFindU, eGetTax, eGetCharge, eSetEmpSalary, eAdv, eNofOps
} eMenuOptions;

const char* str[eNofOps] = {
	"Show All", "Show Company", "Show Users", "Show Employees","Show Bank",
	"Add Company", "Add/Change Package", "Add User", "Add employee","Add area",
	"Sort users", "Find users", "Get company tax", "Get user monthly charge",
	"Set employee monthly salary", "Show advertisement"
};


#define EXIT			-1
#define MC_FILE_TEXT "CableTvServices.txt"
#define MC_FILE_BIN "CableTvServices.bin"


int menu();

