import { BiLike, BiDislike, BiMap } from 'react-icons/bi'
import Image from 'next/image'

import { setPage } from '@/store/slice/countSlice'
import { setPlace } from '@/store/slice/idSlice'
import { useDispatch } from 'react-redux'

export default function PlacePage({ data }) {
	const dispatch = useDispatch()
	const replace = () => {
		dispatch(
			setPlace({
				place_name: data.place_name,
				place_adress: data.adress,
				place_image: data.image[0]
			})
		)
		dispatch(setPage(7))
	}
	return (
		<>
			<div className=' flex justify-between items-center pb-3'>
				<div className=' text-2xl'>{data.place_name}</div>
				{/* <div>
					<button className='p-2 rounded mr-2 bg-slate-100'>
						<BiLike className='text-2xl' />
					</button>
					<button className='p-2 rounded bg-slate-100'>
						<BiDislike className='text-2xl' />
					</button>
				</div> */}
			</div>
			<div id='placelist' className=' overflow-auto whitespace-nowrap w-full'>
				{data.image.map((item, id) => (
					<div
						key={id}
						className=' bg-slate-100  inline-block relative  h-24 w-24 rounded-lg mr-2'
					>
						<Image src={item} fill className='rounded-lg' alt={`image${id}`} />
					</div>
				))}
			</div>
			<div className='flex items-center my-2'>
				<BiMap className='mr-1' />
				{data.adress}
			</div>
			<button
				onClick={() => replace()}
				className='my-2 py-2 border-2 text-center rounded w-full'
			>
				Позвать друзей
			</button>
		</>
	)
}
