[
    {
        state: '',
        host: {
            style:{
                width:200,
            },
            margin:'40',
            padding:'20',
            backgroundColor: 0xffeeeeee,
            // border:'1 0xffcccccc',
        },
        space:{
            style:{
                // flex:1,
            }
        },
        bar:{
            style: {
                // flex:1,
                height:2,
            },
            // margin:'10',
            backgroundColor: 0xffff0000,
            // backgroundColor: 0xff009fff,
        },
        indicator: {
            style: {
                height:20,
                width:20,
                left:-10,
                top:0,
                position:'POSITION_TYPE_ABSOLUTE',
            },
            border:'1 0xff009fff',
            backgroundColor: 0xffffffff,
            radius:'20',
            boxShadow:'0 0 0 0x99000000',

        },
    },
    {
        state: '.hover',
        host:{
            backgroundColor: 0xffdddddd,
        },
        indicator: {
            style:{
            },
            // backgroundColor: 0xffaaaaaa,
            boxShadow:'0 0 5 0x33000000',
        },
    },
]