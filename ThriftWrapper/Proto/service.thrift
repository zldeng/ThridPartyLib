include "struct.thrift"


service GetPerson
{
	struct.ResPerson getPersonInfo(1: struct.Person person)	
}
