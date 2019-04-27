#include "Inventory.h"

void Inventory::intro()
{
	cout<<"*********************************************************"<<"\n";
  cout<<"*************** Welcome To Your Inventory! **************"<<"\n";
  cout<<"*********************************************************"<<"\n";
  cout<<"*********************************************************"<<"\n";
  cout<<"*Bevan Varghese**************************Katyayani Singh*"<<"\n";
  cout<<"*GROUP 44***************************************ENGG1340*"<<"\n";
  cout<<"*********************************************************"<<"\n";
}

void Inventory::menu()
{
	cout<<"\n1. Insert a commodity\n2. Update a commodity\n3. Delete a commodity\n";
  cout<<"4. Search for a commodity (filtered)\n5. Check inventory for stock warnings\n";
	cout<<"6. Display all commodities (filtered\n0. Exit\n";
  cout<<"Enter your choice:"<<"\n";
}

void Inventory::swap(commodity &x, commodity &y)
{
	commodity temp = x;
	x = y;
	y = temp;
}

void Inventory::sortbypopularity(commodity *&item, int count)
{
	for(int i=0;i<count-1;i++) {
		for(int j=0;j<count-i-1;j++) {
			if(item[j].sales<item[j+1].sales) {
				swap(item[j], item[j+1]);
			}
		}
	}
}

void Inventory::sortbyserialnumber(commodity *&item, int count)
{
	for(int i=0;i<count-1;i++) {
		for(int j=0;j<count-i-1;j++) {
			if(item[j].serialno>item[j+1].serialno) {
				swap(item[j], item[j+1]);
			}
		}
	}
}

void Inventory::details(commodity x)
{
  cout<<"|"<<right<<setw(6)<<x.serialno<<"|"<<setw(19)<<x.itemname<<"|"<<setw(20)<<x.manufacturer
  <<"|"<<setw(8)<<x.quantity<<"|"<<setw(7)<<x.sales<<"|"<<setw(8)<<fixed<<setprecision(2)<<x.price<<"|";
  if(x.instock==0)
  cout<<"   NO|"<<"\n";
  else
  cout<<"  YES|"<<"\n";
  return;
}

void Inventory::warn(commodity x)
{
  if(x.quantity==0)
  cout<<"NOTE: \""<<x.manufacturer<<" "<<x.itemname<<"\" is out of stock! Replace immediately."<<"\n";
  else if(x.quantity<=5)
  cout<<"NOTE: \""<<x.manufacturer<<" "<<x.itemname<<"\" is almost out of stock! Replace soon."<<"\n";
  return;
}

void Inventory::increasesize(commodity *&item, int &size)
{
  commodity *temp = new commodity[size+size];
  for(int i=0;i<size;i++) {
    temp[i] = item[i];
  }
  delete [] item;
  item = temp;
  size+=size;
  return;
}

void Inventory::insert(commodity *&item, int &count, int &sncount, int &size)
{
	if(count==size)
	increasesize(item, size);
  cout<<"Enter item name:"<<"\n";
	cin.ignore();
  getline(cin,item[count].itemname);
  cout<<"Enter manufacturer name:"<<"\n";
  getline(cin,item[count].manufacturer);
  cout<<"Enter quantity:"<<"\n";
  cin>>item[count].quantity;
  cout<<"Enter price:"<<"\n";
  cin>>item[count].price;
  if(item[count].quantity==0)
	item[count].instock = 0;
	else
	item[count].instock = 1;
	item[count].sales = 0;
	item[count].serialno = sncount;
	count++;
  sncount++;
}

void Inventory::stockchecker(commodity *&item, int count)
{
  int flag = 0;
  for(int i=0;i<count;i++) {
    if(item[i].quantity<=5)
    flag = 1;
    warn(item[i]);
  }
  if(flag==0)
  cout<<"All commodities are sufficiently stocked!\n";
}

void Inventory::update(commodity *&item, int count)
{
	int sn, choice, n;
	cout<<"Enter serial number of item:"<<"\n";
	cin>>sn;
	int flag = 0;
	for(int i=0;i<count;i++) {
		if(item[i].serialno==sn) {
			flag = 1;
			sn = i;
		}
	}
	if(flag==0)
	{
		cout<<"Invalid serial number!"<<"\n";
		return;
	}
	cout<<"Press\n1 for procurement of items,\n2 for sale of items,\n3 to change the price:\n";
	cin>>choice;
	switch(choice)
	{
		case 1:
		{
			cout<<"Enter number of units of \""<<item[sn].manufacturer<<" "<<item[sn].itemname<<"\" procured:"<<"\n";
			cin>>n;
			item[sn].quantity+=n;
			if(item[sn].quantity>0)
			item[sn].instock = true;
			break;
		}
		case 2:
		{
			cout<<"Enter number of units of \""<<item[sn].manufacturer<<" "<<item[sn].itemname<<"\" sold:"<<"\n";
			cin>>n;
			if(n>item[sn].quantity) {
				cout<<"Invalid entry!"<<"\n";
				break;
			}
			item[sn].quantity-=n;
			item[sn].sales+=n;
			if(item[sn].quantity==0)
			item[sn].instock = false;
			break;
		}
		case 3:
		{
			cout<<"Enter the new price of \""<<item[sn].manufacturer<<" "<<item[sn].itemname<<"\" :"<<"\n";
			cin>>item[sn].price;
			break;
		}
		default:
		{
			cout<<"Invalid entry!"<<"\n";
			break;
		}
	}
	for(int i=0;i<count;i++) {
    warn(item[i]);
  }
}

void Inventory::deletion(commodity *&item, int &count)
{
	int sn;
	cout<<"Enter serial number of commodity:"<<"\n";
	cin>>sn;
	int flag = 0;
	for(int i=0;i<count;i++) {
		if(item[i].serialno==sn) {
			flag = 1;
			sn = i;
			break;
		}
	}
	if(flag==0) {
		cout<<"Invalid serial number!"<<"\n";
		return;
	}
	for(int i=sn;i+1<count;i++) {
		item[i] = item[i+1];
	}
	count--;
	cout<<"Successfully deleted!"<<"\n";
}

void Inventory::search(commodity *&item, int count)
{
	int ch, flag = 0;
	cout<<"Choose your search filter:\n1: Serial Number\n2: Item Name\n3: Manufacturer\n4: Stock Status"<<"\n";
	cin>>ch;
	switch(ch) {
		case 1:
		{
			int sn;
			cout<<"Enter serial number:"<<"\n";
			cin>>sn;
			for(int i=0;i<count;i++) {
				if(item[i].serialno==sn)
				flag = 1;
			}
			if(flag==0)
			cout<<"Item not found!"<<"\n";
			else {
				cout<<"|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
				for(int i=0;i<count;i++) {
					if(item[i].serialno==sn)
					details(item[i]);
				}
			}
			break;
		}
		case 2:
		{
			string name;
			cout<<"Enter item name:"<<"\n";
			cin.ignore();
			getline(cin,name);
			for(int i=0;i<count;i++) {
				if(item[i].itemname==name)
				flag = 1;
			}
			if(flag==0)
			cout<<"Item not found!"<<"\n";
			else {
				cout<<"|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
				for(int i=0;i<count;i++) {
					if(item[i].itemname==name)
					details(item[i]);
				}
			}
			break;
		}
		case 3:
		{
			string name;
			cout<<"Enter manufacturer name:"<<"\n";
			cin.ignore();
			getline(cin,name);
			for(int i=0;i<count;i++) {
				if(item[i].manufacturer==name)
				flag = 1;
			}
			if(flag==0)
			cout<<"Manufacturer not found!"<<"\n";
			else {
				cout<<"|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
				for(int i=0;i<count;i++) {
					if(item[i].manufacturer==name) {
						details(item[i]);
					}
				}
			}
			break;
		}
		case 4:
		{
			int stockch;
			cout<<"Enter 0 for out-of-stock, 1 for in-stock:"<<"\n";
			cin>>stockch;
			for(int i=0;i<count;i++) {
				if(item[i].instock==stockch)
				flag = 1;
			}
			if(flag==0)
			cout<<"No items found!"<<"\n";
			else {
				cout<<"|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
				for(int i=0;i<count;i++) {
					if(item[i].instock==stockch) {
						details(item[i]);
					}
				}
			}
			break;
		}
		default:
		{
			cout<<"Invalid choice!"<<"\n";
		}
	}
	for(int i=0;i<count;i++) {
    warn(item[i]);
  }
}

void Inventory::displayall(commodity *&item, int count)
{
	int ch;
	if(count==0) {
		cout<<"Inventory is empty!\n";
		return;
	}
	cout<<"Enter 1 to sort by serial number, 2 to sort by popularity:"<<"\n";
	cin>>ch;
	switch(ch) {
		case 1:
		{
			cout<<"\n|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
			sortbyserialnumber(item, count);
			for(int i=0;i<count;i++) {
				details(item[i]);
			}
			break;
		}
		case 2:
		{
			cout<<"\n|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
			sortbypopularity(item, count);
			for(int i=0;i<count;i++) {
				details(item[i]);
			}
			break;
		}
	}
	cout<<"\n";
	if(count==1)
	cout<<"There is 1 commodity in the inventory.\n";
	else
	cout<<"There are "<<count<<" commodities in the inventory.\n";
	for(int i=0;i<count;i++) {
    warn(item[i]);
  }
}

void Inventory::readinventoryfromfile(string shopname, commodity *&item, int &count)
{
  ifstream fin;
  fin.open(shopname.c_str());
  if(fin.fail())
  {
    cout<<"Error opening input file."<<endl;
    cout<<"Exiting program."<<endl;
    exit(1);
  }
  string line, temp;
  int startpos, endpos;
  getline(fin, line);
  while(getline(fin, line))
  {
		cout<<line<<"\n";
    startpos = line.find_first_not_of(" ",1);
    endpos = line.find_first_of(".",startpos);
    temp = line.substr(startpos, endpos-startpos);
    item[count].serialno = stoi(temp);
    cout<<item[count].serialno<<endl;
    startpos = line.find_first_not_of(" ",8);
    endpos = line.find_first_of("|",startpos);
    temp = line.substr(startpos, endpos-startpos);
    item[count].itemname = temp;
    startpos = line.find_first_not_of(" ",28);
    endpos = line.find_first_of("|",startpos);
    temp = line.substr(startpos, endpos-startpos);
    item[count].manufacturer = temp;
    startpos = line.find_first_not_of(" ",49);
    endpos = line.find_first_of("|",startpos);
    temp = line.substr(startpos, endpos-startpos);
    item[count].quantity = stoi(temp);
    if(item[count].quantity>0)
    item[count].instock = true;
    else
    item[count].instock = false;
    startpos = line.find_first_not_of(" ",58);
    endpos = line.find_first_of("|",startpos);
    temp = line.substr(startpos, endpos-startpos);
    item[count].sales = stoi(temp);
    startpos = line.find_first_not_of(" ", 66);
    endpos = line.find_first_of("|",startpos);
    temp = line.substr(startpos, endpos-startpos);
    item[count].price = stod(temp);
    count++;
  }
  cout<<"Successfully read from "<<shopname<<"\n"<<endl;
  fin.close();
}

void Inventory::writeinventorytofile(string shopname, commodity *&item, int count)
{
  ofstream fout;
  fout.open(shopname.c_str());
  if(fout.fail())
  {
    cout<<"Error opening output file."<<endl;
    cout<<"Exiting program."<<endl;
    exit(1);
  }
  fout<<"|Sl.No.|     Item Name     |    Manufacturer    |Quantity| Sales |Price($)|Stock|"<<"\n";
  //     012345678901234567890123456789012345678901234567890123456789012345678901234567890
  sortbyserialnumber(item, count);
  commodity x;
  for(int i=0;i<count;i++) {
    x = item[i];
    fout<<"|"<<right<<setw(6)<<x.serialno<<"|"<<setw(19)<<x.itemname<<"|"<<setw(20)<<x.manufacturer
    <<"|"<<setw(8)<<x.quantity<<"|"<<setw(7)<<x.sales<<"|"<<setw(8)<<fixed<<setprecision(2)<<x.price<<"|";
    if(x.instock==0)
    fout<<"   NO|"<<"\n";
    else
    fout<<"  YES|"<<"\n";
  }
  cout<<"Successfully wrote to "<<shopname<<"\n"<<endl;
  fout.close();
}

void Inventory::userchoice(int ch, commodity *&item, int &count, int &sncount, int &size)
{
	switch(ch)
	{
		case 1:
		insert(item, count, sncount, size);
		break;
		case 2:
		update(item, count);
		break;
		case 3:
		deletion(item, count);
		break;
		case 4:
		search(item, count);
		break;
		case 5:
		stockchecker(item, count);
		break;
		case 6:
		displayall(item, count);
		break;
		default:
		cout<<"Invalid choice, try again!"<<"\n";
		break;
	}
}
