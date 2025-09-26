[
    {
        state: '',
        host: {
            style:{
                width:200,
            },
            margin:'40',
            backgroundColor: 0xff444444,
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
            backgroundColor: 0xff00afff,
            // backgroundColor: 0xff009fff,
        },
        indicator: {
            style: {
                height:20,
                width:20,
                top:-10,
                right:-10,
                position:'absolute',
            },
            border:'0 0xff009fff',
            backgroundColor: 0xff666666,
            radius:'20',
            boxShadow:'0 0 0 0x99000000',

        },
    },
    {
        state: '.hover',
        host:{
            backgroundColor: 0xff4f4f4f,
        },
        indicator: {
            style:{
            },
            // backgroundColor: 0xffaaaaaa,
            boxShadow:'0 0 5 0x33000000',
        },
    },
]