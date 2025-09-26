[
    {
        state: '',
        host: {
            style: {
                height:20,
                width:40,
            },
            // margin:'10',
            backgroundColor: 0xff444444,
            radius:'20',
            transition: {
                props:'all',
                duration: 200,
            },
            // border:'1 0xffcccccc',
        },
        indicator: {
            style: {
                height:18,
                width:18,
                left: 1,
            },
            transition: {
                props:'all',
                duration: 200,
            },
            backgroundColor: 0xff666666,
            radius:'20',
            boxShadow:'0 0 0 0x99000000',
        },
    },
     {
         state: '.hover',
         indicator: {
             style:{
             },
             // backgroundColor: 0xffaaaaaa,
             boxShadow:'0 0 5 0x33000000',
         },
     },
    {
        state: '.checked',
        host:{
            backgroundColor: 0xff00a9ff,
        },
        indicator:{
            style:{
                left: 21,
            },
            // backgroundColor: 0xff0039ff,
        }
    },
]