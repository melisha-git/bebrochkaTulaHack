import Image from 'next/image'
import { useDispatch } from 'react-redux'
import { BiMap, BiStar, BiRightArrowAlt } from 'react-icons/bi'

import { randomIntFromInterval } from '@/utils/rand'
import { setId } from '@/store/slice/idSlice.js'
import { setPage } from '@/store/slice/countSlice'

export default function PlaceItem({ data }) {
	const dispatch = useDispatch()
	const replace = () => {
		dispatch(setId(data.id))
		dispatch(setPage(6))
	}
	return (
		<div
			onClick={() => replace()}
			className='flex items-center border rounded-lg mb-2 p-2'
		>
			<div>
				<div className=' relative h-20 w-20 rounded-md bg-slate-100 mr-1'>
					<Image src={data.image[0]} fill className='rounded-md' alt='image' />
				</div>
			</div>

			<div className='grow'>
				<div className=' text-lg font-medium mb-1'>{data.place_name}</div>
				<div className=' flex mb-1'>
					{[...Array(randomIntFromInterval(1, 5))].map((_, i) => (
						<BiStar key={i} className=' text-lg' />
					))}
				</div>

				<div className='flex items-center text-sm'>
					<BiMap className=' mr-1' />
					<div>{data.adress}</div>
				</div>
			</div>
			<div>
				<BiRightArrowAlt className=' text-base' />
			</div>
		</div>
	)
}
