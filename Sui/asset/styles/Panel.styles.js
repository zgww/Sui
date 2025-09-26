[
    {
        state: '',
        host: {
            style: {
                display: "flex",
                direction:"column",
            },
        },
        panel_head: {
            backgroundColor: 0xff444444,
            // padding:'4 16 4 4',
            padding:'0 0 0 0 ',
            style: {
                cursor: 'pointer',
                direction:'row',
            },
            // border:'1 0xffcccccc',
        },
        'panel_head.light_head': {
            backgroundColor: 0x00000000,
		},
        panel_title:{
            // color:0xff555555,
            padding:'4 8',
            style:{
                //flex:1,
            },
        },
        panel_head_label:{
            // color:0xff555555,
            style:{
                //flex:1,
            },
            font_size:13,
            color:0xff888888,
        },
        panel_head_close:{
            color:0xff888888,
            backgroundColor: 0x00000000,
            padding:'0 8 0 8',
            text: ">",
        },
        panel_body:  {
            padding:'8',
            // margin:'8',
            //backgroundColor: 0xfffff1f1,
        },
    },
    {
        state: '.hover',
        host:{
        },
        panel_head:{
            backgroundColor: 0x33ffffff,
        },
        'panel_head.light_head': {
            backgroundColor: 0x08ffffff,
		},
        'panel_head_close.hover':{
            backgroundColor: 0x33ffffff,
        },
    },
    {
        state:'.open',
        panel_head_close:{
            text: "v",
        },
    }
]