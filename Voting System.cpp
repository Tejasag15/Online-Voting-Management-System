#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

string buffer;

class voter
{
	string voter_id, voter_name, dob, gender, booth_no, voter_pswd;
public:
	void unpack();
	void read();
	void read_file();
	void write_file();
	void display();
	void pack();
	int del(string);
	void modify(string);
	int search1(string);

	static int count();
};

class candidate
{
	string candidate_id, candidate_name, gender, party_name, ward_no;
public:
	void unpack();
	void read();
	void read_file();
	void write_file();
	void display();
	void pack();
	int del(string);
	void modify(string);
	int search1(string);

	static int count();
};

class party
{
	string party_name, party_symbol;
public:
	void unpack();
	void read();
	void read_file();
	void write_file();
	void display();
	void pack();
	int del(string);
	void modify(string);
	int search1(string);

	static int count();
};

class ward
{
	string ward_no, ward_area, booth_count;
public:
	void unpack();
	void read();
	void read_file();
	void write_file();
	void display();
	void pack();
	int del(string);
	void modify(string);
	int search1(string);

	static int count();
};

class boothofficer
{
	string boothofficer_id, boothofficer_name, ward_area, ward_no;
public:
	void unpack();
	void read();
	void read_file();
	void write_file();
	void display();
	void pack();
	int del(string);
	void modify(string);
	int search1(string);

	static int count();
};

void voter::read()
{
	cout << "Enter details [voter id, voter name, date of birth, gender, voter password, booth number]\n";
	cin >> voter_id >> voter_name >> dob >> gender >> voter_pswd >> booth_no;
}

void voter::pack()
{
	buffer.erase();
	buffer += voter_id + "|" + voter_name + "|" + dob + "|" + gender + "|" + voter_pswd + "|" + booth_no + "$\n";
}

void voter::read_file()
{
	fstream fp;
	fp.open("voter.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		unpack();
		if (!buffer.empty())
			display();
	}
	fp.close();
}

void voter::unpack()
{
	int i = 0;
	voter_id.erase();
	while (buffer[i] != '|')
		voter_id += buffer[i++];
	i++;

	voter_name.erase();
	while (buffer[i] != '|')
		voter_name += buffer[i++];
	i++;

	dob.erase();
	while (buffer[i] != '|')
		dob += buffer[i++];
	i++;

	gender.erase();
	while (buffer[i] != '|')
		gender += buffer[i++];
	i++;

	voter_pswd.erase();
	while (buffer[i] != '|')
		voter_pswd += buffer[i++];
	i++;

	booth_no.erase();
	while (buffer[i] != '$')
		booth_no += buffer[i++];
}

void voter::display()
{
	cout << "\nVoter Id: " << voter_id << "\nVoter Name: " << voter_name << "\nDate of Birth: " << dob << "\nGender: " << gender << "\nVoter Password: " << voter_pswd << "\nBooth number: " << booth_no << endl;
}

int voter::search1(string vid)
{
	fstream fp;
	int recno = 0, flag = 0, pos = 0;
	fp.open("voter.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		recno++;
		unpack();
		if (voter_id == vid)
		{
			cout << "\nRecord is " << buffer;
			cout << "\nRecord Found at Position " << recno;
			pos = fp.tellg();
			flag = 1;
			return pos;
		}
	}
	fp.close();
	if (!flag)
		cout << "Record not found\n";
	return pos;
}

int voter::del(string vid)
{
	fstream fp;
	char mark = '*', t;
	int pos, flag = 0;
	pos = search1(vid);
	if (pos)
	{
		fp.open("voter.txt", ios::in | ios::out);
		pos -= 2;
		t = fp.get();
		while (t != '$' && pos != 0)
		{
			pos--;
			fp.seekp(pos, ios::beg);
			t = fp.get();
		}

		if (pos != 0)
			fp.seekp(pos + 2, ios::beg);
		else
			fp.seekp(pos, ios::beg);

		fp.put(mark);
		flag = 1;
	}
	fp.close();
	if (!flag)
		return 0;
	else
		return 1;
}

void voter::modify(string vid)
{
	if (del(vid))
	{
		cout << "\nEnter details [voter id, voter name, date of birth, gender, voter password, booth number] to modify\n";
		cin >> voter_id >> voter_name >> dob >> gender >> voter_pswd >> booth_no;
		buffer.erase();
		pack();
		write_file();
	}
}

void voter::write_file()
{
	fstream fp;
	fp.open("voter.txt", ios::out | ios::app);
	fp << buffer;
	fp.close();
}

int voter::count()
{
	int count = 0;
	fstream fp;
	fp.open("voter.txt", ios::in);

	while (!fp.eof()) {
		getline(fp, buffer);
		if (!buffer.empty()) {
			count++;
		}
	}

	fp.close();
	return count;
}

void candidate::read()
{
	cout << "Enter details [Candidate id, candidate name, gender, party name, ward number]\n";
	cin >> candidate_id >> candidate_name >> gender >> party_name >> ward_no;
}

void candidate::pack()
{
	buffer.erase();
	buffer += candidate_id + "|" + candidate_name + "|" + gender + "|" + party_name + "|" + ward_no + "$\n";
}

void candidate::read_file()
{
	fstream fp;
	fp.open("candidate.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		unpack();
		if (!buffer.empty())
			display();
	}
	fp.close();
}

void candidate::unpack()
{
	int i = 0;
	candidate_id.erase();
	while (buffer[i] != '|')
		candidate_id += buffer[i++];
	i++;

	candidate_name.erase();
	while (buffer[i] != '|')
		candidate_name += buffer[i++];
	i++;

	gender.erase();
	while (buffer[i] != '|')
		gender += buffer[i++];
	i++;

	party_name.erase();
	while (buffer[i] != '|')
		party_name += buffer[i++];
	i++;

	ward_no.erase();
	while (buffer[i] != '$')
		ward_no += buffer[i++];
}

void candidate::display()
{
	cout << "\nCandidate Id: " << candidate_id << "\nCandidate Name: " << candidate_name << "\nGender: " << gender << "\nParty Name: " << party_name << "\nWard number: " << ward_no << endl;
}

int candidate::search1(string cid)
{
	fstream fp;
	int recno = 0, flag = 0, pos = 0;
	fp.open("candidate.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		recno++;
		unpack();
		if (candidate_id == cid)
		{
			cout << "\nRecord is " << buffer;
			cout << "\nRecord Found at Position " << recno;
			pos = fp.tellg();
			flag = 1;
			return pos;
		}
	}
	fp.close();
	if (!flag)
		cout << "Record not found\n";
	return pos;
}

int candidate::del(string cid)
{
	fstream fp;
	char mark = '*', t;
	int pos, flag = 0;
	pos = search1(cid);
	if (pos)
	{
		fp.open("candidate.txt", ios::in | ios::out);
		pos -= 2;
		t = fp.get();
		while (t != '$' && pos != 0)
		{
			pos--;
			fp.seekp(pos, ios::beg);
			t = fp.get();
		}

		if (pos != 0)
			fp.seekp(pos + 2, ios::beg);
		else
			fp.seekp(pos, ios::beg);

		fp.put(mark);
		flag = 1;
	}
	fp.close();
	if (!flag)
		return 0;
	else
		return 1;
}

void candidate::modify(string cid)
{
	if (del(cid))
	{
		cout << "\nEnter details [Candidate id, candidate name, gender, party name, ward number] to modify\n";
		cin >> candidate_id >> candidate_name >> gender >> party_name >> ward_no;
		buffer.erase();
		pack();
		write_file();
	}
}

void candidate::write_file()
{
	fstream fp;
	fp.open("candidate.txt", ios::out | ios::app);
	fp << buffer;
	fp.close();
}

int candidate::count()
{
	int count = 0;
	fstream fp;
	fp.open("candidate.txt", ios::in);

	while (!fp.eof()) {
		getline(fp, buffer);
		if (!buffer.empty()) {
			count++;
		}
	}

	fp.close();
	return count;
}

void party::read()
{
	cout << "Enter details [Party name, Party symbol]\n";
	cin >> party_name >> party_symbol;
}

void party::pack()
{
	buffer.erase();
	buffer += party_name + "|" + party_symbol + "$\n";
}

void party::read_file()
{
	fstream fp;
	fp.open("party.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		unpack();
		if (!buffer.empty())
			display();
	}
	fp.close();
}

void party::unpack()
{
	int i = 0;
	party_name.erase();
	while (buffer[i] != '|')
		party_name += buffer[i++];
	i++;

	party_symbol.erase();
	while (buffer[i] != '$')
		party_symbol += buffer[i++];
}

void party::display()
{
	cout << "\nParty Name: " << party_name << "\nParty Symbol: " << party_symbol << endl;
}

int party::search1(string pname)
{
	fstream fp;
	int recno = 0, flag = 0, pos = 0;
	fp.open("party.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		recno++;
		unpack();
		if (party_name == pname)
		{
			cout << "\nRecord is " << buffer;
			cout << "\nRecord Found at Position " << recno;
			pos = fp.tellg();
			flag = 1;
			return pos;
		}
	}
	fp.close();
	if (!flag)
		cout << "Record not found\n";
	return pos;
}

int party::del(string pname)
{
	fstream fp;
	char mark = '*', t;
	int pos, flag = 0;
	pos = search1(pname);
	if (pos)
	{
		fp.open("party.txt", ios::in | ios::out);
		pos -= 2;
		t = fp.get();
		while (t != '$' && pos != 0)
		{
			pos--;
			fp.seekp(pos, ios::beg);
			t = fp.get();
		}

		if (pos != 0)
			fp.seekp(pos + 2, ios::beg);
		else
			fp.seekp(pos, ios::beg);

		fp.put(mark);
		flag = 1;
	}
	fp.close();
	if (!flag)
		return 0;
	else
		return 1;
}

void party::modify(string pname)
{
	if (del(pname))
	{
		cout << "\nEnter details [Party name, Party symbol] to modify\n";
		cin >> party_name >> party_symbol;
		buffer.erase();
		pack();
		write_file();
	}
}

void party::write_file()
{
	fstream fp;
	fp.open("party.txt", ios::out | ios::app);
	fp << buffer;
	fp.close();
}

int party::count()
{
	int count = 0;
	fstream fp;
	fp.open("party.txt", ios::in);

	while (!fp.eof()) {
		getline(fp, buffer);
		if (!buffer.empty()) {
			count++;
		}
	}

	fp.close();
	return count;
}

void ward::read()
{
	cout << "Enter details [Ward number, Ward area, Booth count]\n";
	cin >> ward_no >> ward_area >> booth_count;
}

void ward::pack()
{
	buffer.erase();
	buffer += ward_no + "|" + ward_area + "|" + booth_count + "$\n";
}

void ward::read_file()
{
	fstream fp;
	fp.open("ward.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		unpack();
		if (!buffer.empty())
			display();
	}
	fp.close();
}

void ward::unpack()
{
	int i = 0;
	ward_no.erase();
	while (buffer[i] != '|')
		ward_no += buffer[i++];
	i++;

	ward_area.erase();
	while (buffer[i] != '|')
		ward_area += buffer[i++];
	i++;

	booth_count.erase();
	while (buffer[i] != '$')
		booth_count += buffer[i++];
}

void ward::display()
{
	cout << "\nWard Number: " << ward_no << "\nWard Area: " << ward_area << "\nBooth Count: " << booth_count << endl;
}

int ward::search1(string wno)
{
	fstream fp;
	int recno = 0, flag = 0, pos = 0;
	fp.open("ward.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		recno++;
		unpack();
		if (ward_no == wno)
		{
			cout << "\nRecord is " << buffer;
			cout << "\nRecord Found at Position " << recno;
			pos = fp.tellg();
			flag = 1;
			return pos;
		}
	}
	fp.close();
	if (!flag)
		cout << "Record not found\n";
	return pos;
}

int ward::del(string wno)
{
	fstream fp;
	char mark = '*', t;
	int pos, flag = 0;
	pos = search1(wno);
	if (pos)
	{
		fp.open("ward.txt", ios::in | ios::out);
		pos -= 2;
		t = fp.get();
		while (t != '$' && pos != 0)
		{
			pos--;
			fp.seekp(pos, ios::beg);
			t = fp.get();
		}

		if (pos != 0)
			fp.seekp(pos + 2, ios::beg);
		else
			fp.seekp(pos, ios::beg);

		fp.put(mark);
		flag = 1;
	}
	fp.close();
	if (!flag)
		return 0;
	else
		return 1;
}

void ward::modify(string wno)
{
	if (del(wno))
	{
		cout << "\nEnter details [Ward number, Ward area, Booth count] to modify\n";
		cin >> ward_no >> ward_area >> booth_count;
		buffer.erase();
		pack();
		write_file();
	}
}

void ward::write_file()
{
	fstream fp;
	fp.open("ward.txt", ios::out | ios::app);
	fp << buffer;
	fp.close();
}

int ward::count()
{
	int count = 0;
	fstream fp;
	fp.open("ward.txt", ios::in);

	while (!fp.eof()) {
		getline(fp, buffer);
		if (!buffer.empty()) {
			count++;
		}
	}

	fp.close();
	return count;
}

void boothofficer::read()
{
	cout << "Enter details [Booth Officer id, Booth Officer name, Ward area, Ward number]\n";
	cin >> boothofficer_id >> boothofficer_name >> ward_area >> ward_no;
}

void boothofficer::pack()
{
	buffer.erase();
	buffer += boothofficer_id + "|" + boothofficer_name + "|" + ward_area + "|" + ward_no + "$\n";
}

void boothofficer::read_file()
{
	fstream fp;
	fp.open("boothofficer.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		unpack();
		if (!buffer.empty())
			display();
	}
	fp.close();
}

void boothofficer::unpack()
{
	int i = 0;
	boothofficer_id.erase();
	while (buffer[i] != '|')
		boothofficer_id += buffer[i++];
	i++;

	boothofficer_name.erase();
	while (buffer[i] != '|')
		boothofficer_name += buffer[i++];
	i++;

	ward_area.erase();
	while (buffer[i] != '|')
		ward_area += buffer[i++];
	i++;

	ward_no.erase();
	while (buffer[i] != '$')
		ward_no += buffer[i++];
}

void boothofficer::display()
{
	cout << "\nBooth Officer Id: " << boothofficer_id << "\nBooth Officer Name: " << boothofficer_name << "\nWard Area: " << ward_area << "\nWard number: " << ward_no << endl;
}

int boothofficer::search1(string bid)
{
	fstream fp;
	int recno = 0, flag = 0, pos = 0;
	fp.open("boothofficer.txt", ios::in);
	while (!fp.eof())
	{
		buffer.erase();
		getline(fp, buffer);
		recno++;
		unpack();
		if (boothofficer_id == bid)
		{
			cout << "\nRecord is " << buffer;
			cout << "\nRecord Found at Position " << recno;
			pos = fp.tellg();
			flag = 1;
			return pos;
		}
	}
	fp.close();
	if (!flag)
		cout << "Record not found\n";
	return pos;
}

int boothofficer::del(string bid)
{
	fstream fp;
	char mark = '*', t;
	int pos, flag = 0;
	pos = search1(bid);
	if (pos)
	{
		fp.open("boothofficer.txt", ios::in | ios::out);
		pos -= 2;
		t = fp.get();
		while (t != '$' && pos != 0)
		{
			pos--;
			fp.seekp(pos, ios::beg);
			t = fp.get();
		}

		if (pos != 0)
			fp.seekp(pos + 2, ios::beg);
		else
			fp.seekp(pos, ios::beg);

		fp.put(mark);
		flag = 1;
	}
	fp.close();
	if (!flag)
		return 0;
	else
		return 1;
}

void boothofficer::modify(string bid)
{
	if (del(bid))
	{
		cout << "\nEnter details [Booth Officer id, Booth Officer name, Ward area, Ward number] to modify\n";
		cin >> boothofficer_id >> boothofficer_name >> ward_area >> ward_no;
		buffer.erase();
		pack();
		write_file();
	}
}

void boothofficer::write_file()
{
	fstream fp;
	fp.open("boothofficer.txt", ios::out | ios::app);
	fp << buffer;
	fp.close();
}

int boothofficer::count()
{
	int count = 0;
	fstream fp;
	fp.open("boothofficer.txt", ios::in);

	while (!fp.eof()) {
		getline(fp, buffer);
		if (!buffer.empty()) {
			count++;
		}
	}

	fp.close();
	return count;
}

int main()
{
	voter V;
	candidate C;
	party P;
	ward W;
	boothofficer B;
	int choice;
	string id;

	do
	{
		cout << "\n\n\nMain Menu\n\n1.Voter\n2.Candidate\n3.Party\n4.Ward\n5.Booth Officer\n6.Exit\n\nEnter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			do
			{
				cout << "\n\n\nVOTER MENU\n\n1.Add voter details\n2.Display voter details\n3.Search voter details\n4.Modify voter details\n5.Delete voter details\n6.Count voters\n7.Back to Main Menu\n\nEnter your choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:
					V.read();
					V.pack();
					V.write_file();
					break;

				case 2:
					V.read_file();
					break;

				case 3:
					cout << "\nEnter the Voter ID to search: ";
					cin >> id;
					V.search1(id);
					break;

				case 4:
					cout << "\nEnter the Voter ID to modify: ";
					cin >> id;
					V.modify(id);
					break;

				case 5:
					cout << "\nEnter the Voter ID to delete: ";
					cin >> id;
					V.del(id);
					break;

				case 6:
					cout << "\nTotal number of voters: " << V.count() << endl;
					break;

				case 7:
					break;

				default:
					cout << "Invalid Choice!\n";
				}
			} while (choice != 7);
			break;

		case 2:
			do
			{
				cout << "\n\n\nCANDIDATE MENU\n\n1.Add candidate details\n2.Display candidate details\n3.Search candidate details\n4.Modify candidate details\n5.Delete candidate details\n6.Count candidates\n7.Back to Main Menu\n\nEnter your choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:
					C.read();
					C.pack();
					C.write_file();
					break;

				case 2:
					C.read_file();
					break;

				case 3:
					cout << "\nEnter the Candidate ID to search: ";
					cin >> id;
					C.search1(id);
					break;

				case 4:
					cout << "\nEnter the Candidate ID to modify: ";
					cin >> id;
					C.modify(id);
					break;

				case 5:
					cout << "\nEnter the Candidate ID to delete: ";
					cin >> id;
					C.del(id);
					break;

				case 6:
					cout << "\nTotal number of candidates: " << C.count() << endl;
					break;

				case 7:
					break;

				default:
					cout << "Invalid Choice!\n";
				}
			} while (choice != 7);
			break;

		case 3:
			do
			{
				cout << "\n\n\nPARTY MENU\n\n1.Add party details\n2.Display party details\n3.Search party details\n4.Modify party details\n5.Delete party details\n6.Count parties\n7.Back to Main Menu\n\nEnter your choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:
					P.read();
					P.pack();
					P.write_file();
					break;

				case 2:
					P.read_file();
					break;

				case 3:
					cout << "\nEnter the Party Name to search: ";
					cin >> id;
					P.search1(id);
					break;

				case 4:
					cout << "\nEnter the Party Name to modify: ";
					cin >> id;
					P.modify(id);
					break;

				case 5:
					cout << "\nEnter the Party Name to delete: ";
					cin >> id;
					P.del(id);
					break;

				case 6:
					cout << "\nTotal number of parties: " << P.count() << endl;
					break;

				case 7:
					break;

				default:
					cout << "Invalid Choice!\n";
				}
			} while (choice != 7);
			break;

		case 4:
			do
			{
				cout << "\n\n\nWARD MENU\n\n1.Add ward details\n2.Display ward details\n3.Search ward details\n4.Modify ward details\n5.Delete ward details\n6.Count wards\n7.Back to Main Menu\n\nEnter your choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:
					W.read();
					W.pack();
					W.write_file();
					break;

				case 2:
					W.read_file();
					break;

				case 3:
					cout << "\nEnter the Ward Number to search: ";
					cin >> id;
					W.search1(id);
					break;

				case 4:
					cout << "\nEnter the Ward Number to modify: ";
					cin >> id;
					W.modify(id);
					break;

				case 5:
					cout << "\nEnter the Ward Number to delete: ";
					cin >> id;
					W.del(id);
					break;

				case 6:
					cout << "\nTotal number of wards: " << W.count() << endl;
					break;

				case 7:
					break;

				default:
					cout << "Invalid Choice!\n";
				}
			} while (choice != 7);
			break;

		case 5:
			do
			{
				cout << "\n\n\nBOOTH OFFICER MENU\n\n1.Add booth officer details\n2.Display booth officer details\n3.Search booth officer details\n4.Modify booth officer details\n5.Delete booth officer details\n6.Count booth officers\n7.Back to Main Menu\n\nEnter your choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:
					B.read();
					B.pack();
					B.write_file();
					break;

				case 2:
					B.read_file();
					break;

				case 3:
					cout << "\nEnter the Booth Officer ID to search: ";
					cin >> id;
					B.search1(id);
					break;

				case 4:
					cout << "\nEnter the Booth Officer ID to modify: ";
					cin >> id;
					B.modify(id);
					break;

				case 5:
					cout << "\nEnter the Booth Officer ID to delete: ";
					cin >> id;
					B.del(id);
					break;

				case 6:
					cout << "\nTotal number of booth officers: " << B.count() << endl;
					break;

				case 7:
					break;

				default:
					cout << "Invalid Choice!\n";
				}
			} while (choice != 7);
			break;

		case 6:
			exit(0);

		default:
			cout << "Invalid Choice!\n";
		}
	} while (choice != 6);

	return 0;
}

