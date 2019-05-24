# Amaze competition

## Setup & build
###1. login to the AWS server
run:
`sudo yum install git`
`sudo yum install make`
`sudo yum install gcc`

###2. clone my code:

`git clone https://github.com/chenyunhao/amaze.git && cd amaze`

###3. build
`make`

###4. run
`./run.sh`

## Prebuild result
you can check result.txt file in the project folder

## Conclusion
Actually, I didn't complete the competition. I only can get the 129 levels result. I think all of the is the shortest path.
Finally, I upload the code, if anyone can see my code, maybe give me some advise or can inspire others great guys mind.
Thanks for the competition, I like it :).

Maybe I will use Deep learning to fix this later :)

## One more thing
I have another solution on branch faster_not_shortest. the code can finish the 170 levels in 4 seconds, and get 156 levels result but not shortest. just for fun.
if you want to try:
	`make && ./amaze`
