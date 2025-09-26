[
    {
        state: '',
        host:{
            padding: '8 16',
            margin: '4 4',
            radius: '5', 
            backgroundColor: 0xff333333,
            //colorp:'red',
            transition: {
                props:'all',
                duration: 100,
            },
        },
        label:{
            color: 0xff999999,
            // transition: {
            //     props:'all',
            //     duration: 100,
            // },
        },
    },
    {
        state: '.in_group',
        host: {
            radius: '0', 
            margin:'0',
        },
        'host:first-child': {
            radius: '8 0 0 8', 
            //backgroundColor:0xffff0000,
        },
        'host:last-child': {
            radius: '0 8 8 0', 
            //backgroundColor:0xffffff00,
        },
        'host:first-child:last-child': {
            sort:1,
            radius: '8 8 8 8', 
            //backgroundColor:0xffff0000,
        },
    },
    {
        state: '.onlyicon',
        host: {
            padding: '4 8',
        },
    },
    {
        state: '.hover',
        host:{
            backgroundColor:0xff444444,
        },
        label:{
            color: 0xffaaaaaa,
        },
    },
    {
        state: '.checked',
        host:{
            backgroundColor:0xff303030,
        },
    },

]