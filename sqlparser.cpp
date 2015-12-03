#include<bits/stdc++.h>
#include <fstream>
 
#define mod 1000000007
#define f(i,a,b) for(i=a;i<b;i++)
#define ff(i,a) for(i=0;i<a;i++)
#define sc scanf
#define pr printf
#define clr(a) memset(a,0,sizeof(a))
#define ll long long
#define vi vector<int>
#define pin(n) printf("%d\n",n)
#define pll(n) printf("%lld\n",n)
#define sin(n) scanf("%d",&n)
#define sll(n) scanf("%lld",&n)
#define pins(n) printf("%d ",n)
#define plls(n) printf("%lld ",n)
#define ss(n) scanf("%s",n)
#define nl pr("\n")
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sl(a) strlen(a)
 
using namespace std;

vector<string> cols;                                  // what has to be projected
vector<string> conditions;                            // conditions after where
vector<string> tables;                               // stores tables file name
vector<pair<string,string> > parsed_cols;            // details cols
vector<vector<string> > metadata(10);                // metadata of each file
vector<vector<string> > files(10);                   // stores each file
vector<pair<int,int> > col_index;             
vector<string> output;
vector<string> joined_table;
string joined_metadata;
vector<int> sol_rows;

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

string str_remove_spaces(string a)
{
	int i,j,k,l;
	l=a.size();
	i=0;
	while(i<l && a[i]==' ')
		i++;
	j=l-1;
	while(j>=0 && a[j]==' ')
		j--;

	char temp[1000];
	k=0;

	while(i<=j)
		temp[k++]=a[i++];
	temp[k]='\0';

	string truncated_string(temp);
	return truncated_string;
}

vector<string> str_split(string a,string delim)
{
	string s = a;
	string delimiter = delim;

	vector<string> peices;

	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != -1) 
	{
    	token = s.substr(0, pos);
    	//cout << token << endl;
    	peices.pb(str_remove_spaces(token));
    	s.erase(0, pos + delimiter.length());
	}
	peices.pb(str_remove_spaces(s));
	return peices;
}

void parse_input(string input)
{
	int ls,lf,lc,lt,lw;
	int where_flag=0;
	int cond_no=0;
	string cond_type="NA";
	int i,j,k;
	size_t pos;

	vector<string> from=str_split(input,"from");

	vector<string> select=str_split(from[0],"select");
	cols=str_split(select[1],",");

 	vector<string> where=str_split(from[1],"where");
 	tables=str_split(where[0],",");
 	
 	if(where.size()==2)
 	{
 		where_flag=1;
 		conditions = str_split(where[1],"and");
 		if(conditions.size()==1)
 		{
 			conditions = str_split(conditions[0],"or");
 			if(conditions.size()==2)
 			{
 				cond_no=2;
 				cond_type="OR";
 			}
 			else
 			{
 				cond_no=1;
 				cond_type="NONE";
 			}
 		}
 		else
 		{
 			cond_no=2;
 			cond_type="AND";
 		}
 	}
 	conditions.pb(cond_type);
 	// tables, cols, conditions
}

void parse_cols()
{
	int l,i,j;
	pair<string,string> p;

	if(cols[0]=="*")
	{
		p.first="STAR";
		p.second="*";
		parsed_cols.pb(p);
		return;
	}
	

	vector<string> temp;
	ff(i,cols.size())
	{
		temp=str_split(cols[i],"(");
		if(temp.size()==1)
		{
			p.first="NA";
			p.second=temp[0];
			parsed_cols.pb(p);
		}
		else
		{
			if(temp[0]=="distinct")
				p.first="distinct";

			if(temp[0]=="max")
				p.first="max";

			if(temp[0]=="min")
				p.first="min";

			if(temp[0]=="average")
				p.first="average";

			if(temp[0]=="sum")
				p.first="sum";

			p.second=temp[1].substr(0,temp[1].size()-1);
			parsed_cols.pb(p);
		}
	}
}

void get_files_and_metadata()
{

	int i,j,k,m,n,l;
	char fpath[100];
	string fname;
	
	string line;
	l=tables.size();
	i=0;
	if(i<l)
	{
		line=tables[i]+".csv";
		strcpy(fpath,line.c_str());
		ifstream file1(fpath);
		for(line;getline(file1,line);) 
			files[i].pb(string(line));
		i++;
	}
	if(i<l)
	{
		line=tables[i]+".csv";
		strcpy(fpath,line.c_str());
		ifstream file2(fpath);
		for(line;getline(file2,line);) 
			files[i].pb(string(line));
		i++;
	}
	if(i<l)
	{
		line=tables[i]+".csv";
		strcpy(fpath,line.c_str());
		ifstream file3(fpath);
		for(line;getline(file3,line);) 
			files[i].pb(string(line));
		i++;
	}
	if(i<l)
	{
		line=tables[i]+".csv";
		strcpy(fpath,line.c_str());
		ifstream file4(fpath);
		for(line;getline(file4,line);) 
			files[i].pb(string(line));
		i++;
	}
	if(i<l)
	{
		line=tables[i]+".csv";
		strcpy(fpath,line.c_str());
		ifstream file5(fpath);
		for(line;getline(file5,line);) 
			files[i].pb(string(line));
		i++;
	}


	ifstream file("metadata.txt");
	for(line;getline(file,line);) 
	{
	//	cout << "&&";
	//	cout << line << endl;
		if(line=="<begin_table>")
		{
	//		cout << "**" << endl;
			getline(file,line);
			//line=line.substr(1,line.size()-2);
			ff(j,tables.size())
			{
				if(tables[j]==line)
				{
			//		cout << j << endl;
					break;
				}
			}
			if(j<tables.size())
			{
				while(1)
				{
					getline(file,line);
					if(line=="<end_table>")
						break;
				//	line=line.substr(1,line.size()-2);
					metadata[j].pb(tables[j]+"."+line);
				}
			}
			else
			{
	//			cout << "yeah" << endl;
				while(1)
				{
					getline(file,line);
					if(line=="<end_table>")
						break;
				}
			}
		}
	}

	// -------------------------- Working with Cols ------------------

	size_t pos;
	int flag=0;
	vector<string> temp;
	ff(i,parsed_cols.size())
	{
		flag=0;
		pos=(parsed_cols[i].second).find(".");
		if(pos==-1)
		{
			ff(j,tables.size())
			{
				ff(k,metadata[j].size())
				{
					pos=metadata[j][k].find((parsed_cols[i]).second);
					if(pos!=-1)
					{
						(parsed_cols[i]).second=metadata[j][k];
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
		}
	} 
}

void print()
{

	int i,j,k,row,ans,loop;
	
	vector<string> out;
	vector<string> meta;
	vector<int> id;
	string meta_out="",str1,str2,mad;
	string line,final_out;

	if(parsed_cols[0].first=="STAR")
	{
		cout << joined_metadata << endl;
		ff(i,sol_rows.size())
		{
			cout << joined_table[sol_rows[i]] << endl;
		}
	}
	else
	{
		int beti=0;
		if(parsed_cols[0].first!="NA")
		{
			meta_out="";
			ff(loop,parsed_cols.size())
			{
				str2=parsed_cols[loop].second;
				line=","+parsed_cols[loop].first+"("+str2+")";
				meta_out+=line;
			}
			meta_out.erase(meta_out.begin());
			cout << meta_out << endl;

			final_out="";
			meta_out="";
			ff(loop,parsed_cols.size())
			{
				str1=parsed_cols[loop].first;
				str2=parsed_cols[loop].second;

				meta=str_split(joined_metadata,",");
				ff(i,meta.size())
				{
					if(str2==meta[i])
					{
						k=i;
						break;
					}
				}
				if(str1=="distinct")
				{
					line="distinct("+str2+")";
					beti=1;
				//	cout << line << endl;
					ff(i,sol_rows.size())
					{
						row=sol_rows[i];
						meta=str_split(joined_table[row],",");
						ff(j,out.size())
						{
							if(out[j]==meta[k])
								break;
						}
						if(j==out.size())
							out.pb(meta[k]);
					}
					ff(i,out.size())
						cout << out[i] << endl;
				}
				if(str1=="sum")
				{
					ans=0;
					line=",sum("+str2+")";
					meta_out+=line;
				//	cout << line << endl;
					ff(i,sol_rows.size())
					{
						row=sol_rows[i];
						meta=str_split(joined_table[row],",");
						ans+=atoi(meta[k].c_str());
					}
				//	cout << ans << endl;
					
					if(loop==0)
						cout<<ans;
					else
					{
						cout << "," << ans;
					}
				}
				if(str1=="max")
				{
					ans=0;
					line=",max("+str2+")";
					meta_out+=line;
				//	cout << line << endl;
					ff(i,sol_rows.size())
					{
						row=sol_rows[i];
						meta=str_split(joined_table[row],",");
						if((atoi(meta[k].c_str()))>ans)
							ans=(atoi(meta[k].c_str()));
					}
				//	cout << ans << endl;
					
					if(loop==0)
						cout<<ans;
					else
					{
						cout << "," << ans;
					}
				}
				if(str1=="min")
				{
					ans=INT_MAX;
					line=",min("+str2+")";
					meta_out+=line;
				//	cout << line << endl;
					ff(i,sol_rows.size())
					{
						row=sol_rows[i];
						meta=str_split(joined_table[row],",");
						if((atoi(meta[k].c_str()))<ans)
							ans=(atoi(meta[k].c_str()));
					}
				//	cout << ans << endl;
				
					if(loop==0)
						cout<<ans;
					else
					{
						cout << "," << ans;
					}
				}
				if(str1=="average")
				{
					float anss=0;
					line=",average("+str2+")";
					meta_out+=line;
				//	cout << line << endl;
					ff(i,sol_rows.size())
					{
						row=sol_rows[i];
						meta=str_split(joined_table[row],",");
						anss+=atoi(meta[k].c_str());
					}
					anss=anss/sol_rows.size();
					if(loop==0)
						printf("%0.2f",anss);
					else
					{
						printf(",%0.2f",anss);
					}
					
				}
			}
			if(beti!=1)
				cout << endl;

		}
		else
		{
			meta=str_split(joined_metadata,",");
			ff(i,parsed_cols.size())
			{
				ff(j,meta.size())
				{
					if(parsed_cols[i].second==meta[j])
					{
						meta_out+=","+meta[j];
						id.pb(j);
						break;
					}
				}
			}
			meta_out.erase(meta_out.begin());

			cout << meta_out << endl;
		
			ff(i,sol_rows.size())
			{
				row=sol_rows[i];
				line="";
				meta=str_split(joined_table[row],",");
				ff(j,id.size())
				{
					k=id[j];
					line+=","+meta[k];
				}
				line.erase(line.begin());
				cout << line << endl;
			}
		}

	}
}

vector<int> check_cond(string lhs,string rhs,int type,int op)
{

	//cout << lhs << " " << rhs << " " << type << " " << op << endl;
	int i,j,k,l,m,val;
	vector<int> local_sol;
	vector<string> meta;
	string line;
	vector<int> temp1,temp2;            

	if(type==1)
	{
		meta=str_split(joined_metadata,",");
		ff(i,meta.size())
		{
			if(meta[i]==lhs)
			{
				k=i;
				break;
			}
		}
		ff(i,joined_table.size())
		{
			line=joined_table[i];
			meta=str_split(line,",");                           // <=:1, >=2, =:3, <:4, >:5
			temp1.clear();
			ff(j,meta.size())
				temp1.pb(atoi(meta[j].c_str()));
			val=atoi(rhs.c_str());
			if(op==1)
			{	
				if(temp1[k]<=val)
					local_sol.pb(i);
			}
			if(op==2)
			{	
				if(temp1[k]>=val)
					local_sol.pb(i);
			}
			if(op==3)
			{	
				if(temp1[k]==val)
					local_sol.pb(i);
			}
			if(op==4)
			{	
				if(temp1[k]<val)
					local_sol.pb(i);
			}
			if(op==5)
			{	
				if(temp1[k]>val)
					local_sol.pb(i);
			}
		}
	}
	else
	{
	//	cout << joined_metadata << endl;
		meta=str_split(joined_metadata,",");
		ff(i,meta.size())
		{
			if(meta[i]==lhs)
			{
				k=i;
				break;
			}
		}
		ff(i,meta.size())
		{
			if(meta[i]==rhs)
			{
				l=i;
				break;
			}
		}
	//	cout << k << " " << l << endl;
		ff(i,joined_table.size())
		{
			line=joined_table[i];

			meta=str_split(line,",");
			temp1.clear();
		
			ff(j,meta.size())
				temp1.pb(atoi(meta[j].c_str()));

			if(op==1)
			{	
				if(temp1[k]<=temp1[l])
					local_sol.pb(i);
			}
			if(op==2)
			{	
				if(temp1[k]>=temp1[l])
					local_sol.pb(i);
			}
			if(op==3)
			{	
				if(temp1[k]==temp1[l])
					local_sol.pb(i);
			}
			if(op==4)
			{	
				if(temp1[k]<temp1[l])
					local_sol.pb(i);
			}
			if(op==5)
			{	
				if(temp1[k]>temp1[l])
					local_sol.pb(i);
			}
		}
	//	cout << "aya" << endl;
	}
	return local_sol;
}

void execute()
{
	int i,j,k,l,m,n,flag=0,l1,l2;
	int fileno,index,op;
	string line,dlim;
	vector<string> parsed_conds;
	vector<string> meta;
	vector<string> rhs;
	vector<int> query1,query2;
	size_t pos;
	vector<string> temp;
	
	l=tables.size();
	k=files[0].size();
	ff(i,k)
	{
		joined_table.pb(files[0][i]);
	}


	k=0;
	while(k+1<l)
	{
		l1=joined_table.size();
		l2=files[k+1].size();

		files[k].clear();

		ff(i,l1)
			ff(j,l2)
			{
				line="";
				line=joined_table[i]+","+files[k+1][j];
				files[k].pb(line);
			}

		joined_table.clear();
		ff(i,files[k].size())
			joined_table.pb(files[k][i]);
		k++;
	}

//	cout << tables.size() << endl;
//	cout << metadata[0].size() << endl;

	joined_metadata="";
	
	ff(i,metadata.size())
		ff(j,metadata[i].size())
			joined_metadata+=","+metadata[i][j];




	//joined_metadata.erase(joined_metadata.begin());
//	cout << "here" << endl;
//	cout << joined_metadata << endl;

//	cout << conditions.size() << endl;

	if(conditions.size()==1)
	{
		
		ff(i,joined_table.size())
			sol_rows.pb(i);             // <=:1, >=2, =:3, <:4, >:5
	}

	op=0;
	if(conditions.size()==2)
	{
		pos=conditions[0].find("<=");
		if(pos!=-1)
		{
			dlim="<=";
			op=1;
		}
		if(!op)
		{
			pos=conditions[0].find(">=");
			if(pos!=-1)
			{
				dlim=">=";
				op=2;
			}
		}
		if(!op)
		{
			pos=conditions[0].find("=");
			if(pos!=-1)
			{
				dlim="=";
				op=3;
			}
		}
		if(!op)
		{
			pos=conditions[0].find("<");
			if(pos!=-1)
			{
				dlim="<";
				op=4;
			}
		}
		if(!op)
		{
			pos=conditions[0].find(">");
			if(pos!=-1)
			{
				dlim=">";
				op=5;
			}
		}

		parsed_conds=str_split(conditions[0],dlim);
		flag=0;
		pos=(parsed_conds[0]).find(".");
		if(pos==-1)
		{
			ff(j,tables.size())
			{
				ff(k,metadata[j].size())
				{
					pos=metadata[j][k].find(parsed_conds[0]);
					if(pos!=-1)
					{
						parsed_conds[0]=metadata[j][k];
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
		}
		
		rhs=str_split(parsed_conds[1],".");
		if(rhs.size()==1)
		{
			
			if(parsed_conds[1].at(0)=='-')
			{
				sol_rows=check_cond(parsed_conds[0],parsed_conds[1],1,op);
			}
			else
			{
				k=is_number(parsed_conds[1]);
				if(k>0)
					sol_rows=check_cond(parsed_conds[0],parsed_conds[1],1,op);
				else
				{
					flag=0;
					ff(j,tables.size())
					{
						ff(k,metadata[j].size())
						{
							pos=metadata[j][k].find(parsed_conds[1]);
							if(pos!=-1)
							{
								parsed_conds[1]=metadata[j][k];
								flag=1;
								break;
							}
						}
						if(flag==1)
							break;
					}
					sol_rows=check_cond(parsed_conds[0],parsed_conds[1],2,op);
				}
			}	
		}
		else
		{
		//	cout << "yes" << endl;
			pos=parsed_conds[1].find(".");
			if(pos==-1)
			{
				flag=0;
				ff(j,tables.size())
				{
					ff(k,metadata[j].size())
					{
						pos=metadata[j][k].find(parsed_conds[1]);
						if(pos!=-1)
						{
							parsed_conds[1]=metadata[j][k];
							flag=1;
							break;
						}
					}
					if(flag==1)
						break;
				}
			}
			
		//	cout << parsed_conds[0] << " " << parsed_conds[1] << endl;

			sol_rows=check_cond(parsed_conds[0],parsed_conds[1],2,op);
		//	cout << "no" << endl;
		}
	}
	op=0;


	if(conditions.size()==3)
	{
		pos=conditions[0].find("<=");
		if(pos!=-1)
		{
			dlim="<=";
			op=1;
		}
		if(!op)
		{
			pos=conditions[0].find(">=");
			if(pos!=-1)
			{
				dlim=">=";
				op=2;
			}
		}
		if(!op)
		{
			pos=conditions[0].find("=");
			if(pos!=-1)
			{
				dlim="=";
				op=3;
			}
		}
		if(!op)
		{
			pos=conditions[0].find("<");
			if(pos!=-1)
			{
				dlim="<";
				op=4;
			}
		}
		if(!op)
		{
			pos=conditions[0].find(">");
			if(pos!=-1)
			{
				dlim=">";
				op=5;
			}
		}
		parsed_conds=str_split(conditions[0],dlim);
		flag=0;
		pos=(parsed_conds[0]).find(".");
		if(pos==-1)
		{
			ff(j,tables.size())
			{
				ff(k,metadata[j].size())
				{
					pos=metadata[j][k].find(parsed_conds[0]);
					if(pos!=-1)
					{
						parsed_conds[0]=metadata[j][k];
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
		}
		rhs=str_split(parsed_conds[1],".");
		if(rhs.size()==1)
		{
			if(parsed_conds[1].at(0)=='-')
			{
				query1=check_cond(parsed_conds[0],parsed_conds[1],1,op);
			}
			else
			{
				k=is_number(parsed_conds[1]);
				if(k>0)
					query1=check_cond(parsed_conds[0],parsed_conds[1],1,op);
				else
				{
					flag=0;
					ff(j,tables.size())
					{
						ff(k,metadata[j].size())
						{
							pos=metadata[j][k].find(parsed_conds[1]);
							if(pos!=-1)
							{
								parsed_conds[1]=metadata[j][k];
								flag=1;
								break;
							}
						}
						if(flag==1)
							break;
					}
					query1=check_cond(parsed_conds[0],parsed_conds[1],2,op);
				}
			}
		}
		else
		{
			pos=parsed_conds[1].find(".");
			if(pos==-1)
			{
				flag=0;
				ff(j,tables.size())
				{
					ff(k,metadata[j].size())
					{
						pos=metadata[j][k].find(parsed_conds[1]);
						if(pos!=-1)
						{
							parsed_conds[1]=metadata[j][k];
							flag=1;
							break;
						}
					}
					if(flag==1)
						break;
				}
			}
			
		//	cout << parsed_conds[0] << " " << parsed_conds[1] << endl;

			query1=check_cond(parsed_conds[0],parsed_conds[1],2,op);
		}

		op=0;
		pos=conditions[1].find("<=");
		if(pos!=-1)
		{
			dlim="<=";
			op=1;
		}
		if(!op)
		{
			pos=conditions[1].find(">=");
				if(pos!=-1)
			{
				dlim=">=";
				op=2;
			}
		}
		if(!op)
		{
			pos=conditions[1].find("=");
			if(pos!=-1)
			{
				dlim="=";
				op=3;
			}
		}
		if(!op)
		{
			pos=conditions[1].find("<");
			if(pos!=-1)
			{
				dlim="<";
				op=4;
			}
		}
		if(!op)
		{
			pos=conditions[1].find(">");
			if(pos!=-1)
			{
				dlim=">";
				op=5;
			}
		}
		parsed_conds=str_split(conditions[1],dlim);
		flag=0;
		pos=(parsed_conds[0]).find(".");
		if(pos==-1)
		{
			ff(j,tables.size())
			{
				ff(k,metadata[j].size())
				{
					pos=metadata[j][k].find(parsed_conds[0]);
					if(pos!=-1)
					{
						parsed_conds[0]=metadata[j][k];
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
		}
		rhs=str_split(parsed_conds[1],".");
		if(rhs.size()==1)
		{
			if(parsed_conds[1].at(0)=='-')
			{
				query2=check_cond(parsed_conds[0],parsed_conds[1],1,op);
			}
			else
			{
				k=is_number(parsed_conds[1]);
				if(k>0)
					query2=check_cond(parsed_conds[0],parsed_conds[1],1,op);
				else
				{
					flag=0;
					ff(j,tables.size())
					{
						ff(k,metadata[j].size())
						{
							pos=metadata[j][k].find(parsed_conds[1]);
							if(pos!=-1)
							{
								parsed_conds[1]=metadata[j][k];
								flag=1;
								break;
							}
						}
						if(flag==1)
							break;
					}
					query2=check_cond(parsed_conds[0],parsed_conds[1],2,op);
				}
			}
		}
		else
		{
			pos=parsed_conds[1].find(".");
			if(pos==-1)
			{
				flag=0;
				ff(j,tables.size())
				{
					ff(k,metadata[j].size())
					{
						pos=metadata[j][k].find(parsed_conds[1]);
						if(pos!=-1)
						{
							parsed_conds[1]=metadata[j][k];
							flag=1;
							break;
						}
					}
					if(flag==1)
						break;
				}
			}
			
		//	cout << parsed_conds[0] << " " << parsed_conds[1] << endl;

			query2=check_cond(parsed_conds[0],parsed_conds[1],2,op);
		}
		if(conditions[2]=="AND")
		{
			i=0;j=0;
			while(i<query1.size() && j<query2.size())
			{
				if(query1[i]==query2[j])
				{
					sol_rows.pb(query1[i]);
					i++;j++;
				}
				else if(query1[i]<query2[j])
					i++;
				else
					j++;
			}
		}
		else
		{
			i=0;j=0;
			while(i<query1.size() && j<query2.size())
			{
				if(query1[i]==query2[j])
				{
					sol_rows.pb(query1[i]);
					i++;j++;
				}
				else if(query1[i]<query2[j])
				{
					sol_rows.pb(query1[i]);
					i++;
				}
				else
				{
					sol_rows.pb(query2[j]);
					j++;
				}
			}
			while(i<query1.size())
				sol_rows.pb(query1[i++]);
			while(j<query2.size())
				sol_rows.pb(query2[j++]);
		}

	} 

}

int main(int argc, char *argv[])
{
	
	string delimiter;
	int i,j,k,l,m,n,p,q,r,s,t;
	char fname1[100],fname2[100];

	string input(argv[1]);
	
	parse_input(input);



	parse_cols();

	get_files_and_metadata();

	execute();
//	cout << "assign" << endl;
	print();
	
	return 0;
}