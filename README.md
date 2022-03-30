### JustForFun-CallforCode_SCDFXIBM
Hi! My name is Wei Li and I'm currently pursuing a diploma in electrical engineering at Ngee Ann Polytechnic. I'm also the sole member of this project. 

### Idea Proposal 
a) The goal of my project is to prevent the spread of COVID-19 between the elderly residents. Through the use of technology, I hope to encourage safe distancing measures and educate them on its importance. My idea, the "KeepMeSafe" consists of an ESP8266 board connected with a buzzer that sounds when social distancing rules have been violated. In addition, the ESP8266 is connected to IBM's Node-RED IoT platform. Using a SMS API, Node-RED is able to send SMS notifications to those who have violated social distancing measures. These SMS notifications seek to educate and inform them on the importance of mainintaining social distance and other safety guidelines to adhere to during the COVID-19 season.

### [Pitch Video]
My pitch video for the call for code challenge. Just to add on, my project aims to deal with the problem statement "Preventing the Spread" 

### Architecture of proposed solution
![IoT_Architecture](https://user-images.githubusercontent.com/62842333/84574201-6c9ca300-add7-11ea-9b4a-06242e5a198c.PNG)

### [Detailed Solution](https://github.com/WeiLiToh/Teamless-CallforCode_SCDFXIBM/blob/master/Detailed%20Solution.md)

## Project Roadmap/Proposed Timeline
- My Project "KeepMeSafe" currently gathers the temperature, humidity, echo time and distance and sends the data as a JSON object to the IBM cloud for processing
- It processes the data and decides whether to send a SMS to the user based on whether the user has violated social distancing measures.

**Proposed Timeline** 
- Distribution of the "KeepMeSafe" device and monitor the spread of community cases, especially amongst the elderly citizens.
- Explore ways to enhance the use of the device (Use of a better sensor).
- Possible incorporation with the "tracetogether" app that would help track the effectiveness of such devices (Tracking linked cases and finding out is users have worn the "KeepMeSafe" device.

**Longer term goals:**
- Wide rollout of KeepMeSafe for elderly citizens all over the world
- Reduce the transmission of COVID-19 amongst the elderly population

### [Step-by-step guide on installing the required software and how to run a demo of the solution](https://github.com/WeiLiToh/Teamless-CallforCode_SCDFXIBM/blob/master/Setup.md)

### Running the tests for the proposed solution  
My proposed solution aims to reduce the spread of COVID-19 between elderly residents in Singapore. It requires a wide rollout of the product for an observable difference. To assess the effectiveness of the proposed solution, analysis of the COVID-19 cases has to be conducted as well. In analysing the COVID-19 cases, we seek to understand if those are infected with COVID-19 are wearing KeepMeSafe and whether they have violated any social distancing measures. 

### Links to Demo
[Part 1 - Hardware Demo](https://www.youtube.com/watch?v=hS0L2FkoBqM)

[Part 2 - Node-Red Flow](https://www.youtube.com/watch?v=FwYt-SraZNI)

[Part 3 - Real Life Implementation](https://www.youtube.com/watch?v=iLj0dj2yafk)

### Softwares/Platforms used 
- [IBM IoT Platform](https://www.ibm.com/internet-of-things/solutions/iot-platform/watson-iot-platform)
- [Node-RED](https://nodered.org/)
- [Nexmo](https://developer.nexmo.com/)
- [Arduino IDE](https://www.arduino.cc/)

# Authors
- Toh Wei Li
