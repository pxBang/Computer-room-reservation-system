#include"manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器 获取到所有文件中 学生、老师信息
	this->initVector();

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;

	while (ifs >> com.m_ComId && ifs >> com.m_Maxnum)
	{
		vCom.push_back(com);
	}
	ifs.close();
	//cout << "机房数量: " << vCom.size() << endl;
	

}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员: " << this->m_Name << "登录! " << endl;
	cout << "\t\t -----------------------------------------\n";
	cout << "\t\t|                                        |\n";
	cout << "\t\t|               1 添加账号               |\n";
	cout << "\t\t|                                        |\n";
	cout << "\t\t|               2 查看账号               |\n";
	cout << "\t\t|                                        |\n";
	cout << "\t\t|               3 查看机房               |\n";
	cout << "\t\t|                                        |\n";
	cout << "\t\t|               4 清空预约               |\n";
	cout << "\t\t|                                        |\n";
	cout << "\t\t|               0 注销登录               |\n";
	cout << "\t\t|                                        |\n";
	cout << "\t\t -----------------------------------------\n";
	cout << "请选择您的操作: " << endl;

}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号类型: " << endl;
	cout << "1 添加学生" << endl;
	cout << "2 添加老师" << endl;

	string fName;	//操作文件名
	string tip;		//提示id号
	string errTip;	//重复错误提示

	ofstream ofs;	//文件操作对象

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//添加的是学生
		fName = STUDENT_FILE;
		tip = "请输入学号: ";
		errTip = "学号重复，请重新输入";
		
	}
	else
	{
		fName = TEACHER_FILE;
		tip = "请输入职工编号: ";
		errTip = "职工编号重复，请重新输入";

	}

	//利用追加的方式写文件
	ofs.open(fName, ios::out | ios::app);
	
	int id;		//学号 /职工号
	string name;//姓名
	string pwd;	//密码
	
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		
		//检测学号/职工编号重复
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errTip << endl;
		}
		else
		{
			break;
		}

	}

	cout << "请输入姓名: " << endl;
	cin >> name;
	
	cout << "请输入密码: " << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	
	ofs.close();

	//调用初始化容器接口 重新获取文件中的数据
	this->initVector();



	system("pause");
	system("cls");
	return;



}

void printStudent(Student& s)
{
	cout << "学号: " << s.m_Id << "	姓名: " << s.m_Name << "	密码: " << s.m_Pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "职工编号: " << t.m_EmpId << "	姓名: " << t.m_Name << "	密码: " << t.m_Pwd << endl;
}



//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容: " << endl;
	cout << "1 查看所有学生" << endl;
	cout << "2 查看所有老师" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//查看学生
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		//查看教师
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");

}

//查看机房信息
void Manager::showComputerRoom()
{
	cout << "机房信息如下: " << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号: " << it->m_ComId << "	机房最大容量: " << it->m_Maxnum << endl;
	}
	system("pause");
	system("cls");

}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功!" << endl;
	system("pause");
	system("cls");

}


//初始化容器
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//读取信息	学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "当前学生数量为: " << vStu.size() << endl;
	ifs.close();


	//读取信息	老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "当前老师数量为: " << vTea.size() << endl;

	ifs.close();
}


//检测重复	参数1 检测学号/职工号	参数2 检测类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_Id == id)
			{
				//检测到重复学生学号
				return true;
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (it->m_EmpId == id)
			{
				//检测到重复职工编号
				return true;
			}
		}

	}
	return false;
}

