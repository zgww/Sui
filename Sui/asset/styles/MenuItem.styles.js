[
    {
        state: '',
        host: {
            padding: '4 16',
            radius: '5',

			GridLayoutItem: {
				columnTemplate: '1fr 1fr'
			},
        },
        label: {
            color: 0xff555555,
            font_size:12,
        },
    },
    {
        state: '.hover',
        host: {
            backgroundColor: 0xffefefef,
        },
        label: {
            color: 0xff773333,
        },
    },
    {
        state: '.checked,.current',
        host: {
            backgroundColor: 0xffefefef,
        },
        label: {
            color: 0xff773333,
        },
    },
]