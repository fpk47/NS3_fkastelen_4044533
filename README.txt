In order to properly run this NS3 script you need to:

- Place the ‘fkastelen_script.c’ NS3 script in the ‘scratch’ folder
- Copy the folder ‘fkastelein’ to the main NS3 folder where ‘waf’ is located.

- Go in your terminal (in mac) application and go to the ‘folder’ fkastelein and you can run the python scripts use the commands: 

	‘python run_DataSize.py’
	‘python run_PacketSize.py’
	‘python run_Distance.py’

to start the simulations. Before doing:

	‘python plotData_DataRate_Total.py’
	‘python plotData_DataRate_PerNode.py’
	‘python plotData_PacketSize_Total.py’
	‘python plotData_PacketSize_PerNode.py’
	‘python plotData_Distance_Standing.py’
	‘python plotData_Distance_Moving.py’

MAKE SURE THAT YOU FIRST RUN THE SIMULATIONS OR USE THE DATA ALREADY PROVIDED

- ‘run_DataSize.py’, ‘run_PacketSize.py’ and ‘run_Distance.py’ will automatically regenerate the .txt files.