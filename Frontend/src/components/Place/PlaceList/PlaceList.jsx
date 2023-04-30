import { useSelector } from 'react-redux'

import PlaceItem from '@/components/Place/PlaceList/PlaceItem'
import { getByCategory } from '@/service/place.service.js'
import Link from 'next/link'

export default function Place() {
	const count = useSelector(state => state.idReducer.category)
	const { data, isSuccess } = getByCategory(count)
	return (
		<div className=' max-h-96 overflow-y-scroll' id='placelist'>
			{isSuccess && data.map((item, id) => <PlaceItem data={item} key={id} />)}
			<Link href='/'>
				<button className='w-full border py-1 px-2 rounded text-slate-400'>
					Выбрать другие места
				</button>
			</Link>
		</div>
	)
}
